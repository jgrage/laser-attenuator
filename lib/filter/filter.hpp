/* filter.hpp
 * Jonas
 */
#ifndef FILTER_HPP
#define FILTER_HPP
    
typedef enum FILTER_STATE{REMOVED = 0, INSERTED = 1, MOVING = 2} FILTER_STATE;

/* -------------
 * Generic filter
 * -------------
 */
class filter
{
    public:
        void connect(int enable_pin, int encoder_inserted_pin, int encoder_removed_pin);
        void remove();
        void insert();
        void update_state();
        FILTER_STATE state;
        
    private:

    protected:
        int _encoder_inserted_pin;
        int _encoder_removed_pin;
        int _enable_pin;
        
};

#endif
