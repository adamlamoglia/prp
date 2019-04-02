
using namespace std;

class Vehicle{

    private:

            int capacity;
            int id;

    public:

        Vehicle(int id, int capacity);

        void setCapacity(int capacity);
        void setId(int id);

        int getCapacity();
        int getId();


}