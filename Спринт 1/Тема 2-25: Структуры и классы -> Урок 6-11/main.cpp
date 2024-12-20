#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
public:
    // Включает телевизор.
    void TurnOn() {
        // Напишите код этого метода.
        is_turned_on_ = true;
    }

    // Выключает телевизор.
    void TurnOff() {
        // Напишите код этого метода.
        is_turned_on_ = false;
    }

    // Возвращает true, если телевизор включён и false, если телевизор выключен.
    bool IsTurnedOn() {
        // Напишите код этого метода.
        return is_turned_on_;
    }

    // Возвращает номер текущего канала либо 0, если телевизор был выключен.
    // Номер канала не сбрасывается при выключении и повторном включении.
    // При первом включении телевизор показывает канал № 1.
    int GetCurrentChannel() {
        // Напишите код этого метода.
        if (IsTurnedOn()) {
            return current_channel_;
        }
        return 0;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала или телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        // Напишите код этого метода.
        if (IsTurnedOn() && channel > 0 && channel < 100) {
            current_channel_ = channel;
            return true;
        }
        return false;
    }
private:
    bool is_turned_on_ = false;
    int current_channel_ = 1;
};

int main() {
    TV tv;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << "SelectChannel(25) returned " << tv.SelectChannel(25) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;

    cout << "SelectChannel(0) returned " << tv.SelectChannel(0) << endl;
    cout << "SelectChannel(100) returned " << tv.SelectChannel(100) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn OFF"s << endl;
    tv.TurnOff();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    
    cout << "SelectChannel(15) returned " << tv.SelectChannel(15) << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
}
