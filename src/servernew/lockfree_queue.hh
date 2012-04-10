#ifndef GUARD_DARK_MIR_LOCKFREE_QUEUE_HH_INCLUDED
#define GUARD_DARK_MIR_LOCKFREE_QUEUE_HH_INCLUDED

#include <atomic>

enum MirQueueConstants {
	MIR_CACHE_LINE_SIZE = 64
};

template< typename T >
class lock_free_queue {
private:
	struct node {
		node( T const & value_ ) 
		: value( new T(value_) )
		, next( 0 ) 
		{}

		~node() {
			delete value;
		}

		T * value;
		std::atomic<node*> next;
		char pad[MIR_CACHE_LINE_SIZE - sizeof(value) - sizeof(next)];
	};

	char pad0[MIR_CACHE_LINE_SIZE];

	node * first;
	char pad1[MIR_CACHE_LINE_SIZE - sizeof(first)];

	std::atomic<bool> consumer_lock;
	char pad2[MIR_CACHE_LINE_SIZE - sizeof(consumer_lock)];

	node * last; 	// shared
	char pad3[MIR_CACHE_LINE_SIZE - sizeof(node*)];

	std::atomic<bool> producer_lock;
	char pad4[MIR_CACHE_LINE_SIZE - sizeof(producer_lock)];
public:
	lock_free_queue() 
	: pad0()
	, first(new node( T() ) ) 	// Dummy node
	, pad1()
	, consumer_lock(false)		// Not yet accquired
	, pad2()
	, last( first )			// first == last (next = 0 in both cases)
	, pad3()
	, producer_lock(false)		// Not yet accquired
	, pad4()
	{}

	~lock_free_queue() {
		clean(0); // Clean up left items
	}

	void push( T const & value ) {
		node * tmp = new node(value);			// Create new node
		while( producer_lock.exchange( true ) ) {} 	// wanted endless loop - accquiring the lock
		last->next.exchange(tmp);			// set new next node to the new one
		last = tmp;					// replace the last node with the new node to act as new last one
		producer_lock = false;				// release lock
	}

	bool pop( T & result ) {
		while( consumer_lock.exchange( true ) ) {}	// wanted endless loop - accquiring the lock
		node * f = first;		// Store the pointer so it can't get replaced
		node * n = first->next;		// Also get the next pointer
		if( n ) {			// Queue empty?
			T * value = n->value; 	// Obtain value
			n->value = 0;		// Clear value
			first = n;		// swap first/next
			consumer_lock = false;	// allow next consumer to continue
			result = *value;	// return value assignment
			delete f;		// free old first node
			delete value;		// free value
			return true;		// report success
		}
		
		consumer_lock = false;		// unlock consumer lock
		return false;			// report empty queue
	}

private:
	void clean( node * where ) {
		while( first != where ) {	// clean up if !<where> 
			node * tmp = first;	// get pointer
			first = tmp->next;	// set first to next pointer
			delete tmp;		// free node (will delete value by itself)
		}
	}
	
};

#endif //GUARD_DARK_MIR_LOCKFREE_QUEUE_HH_INCLUDED

