// остановка.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



double generateRandomTime(double avgTime) {
    return -avgTime * log(1.0 - (double)rand() / RAND_MAX);
}

class bus {
    int maxPeopOnStop;
    double avgPassengerT;
    double avgBusTime;
    int maxBus;
    int peopleOnStop;
    bool isTerminal;

public:
    bus(int maxPeople, double avgPasT, double avgBusT, int maxCapacity, bool terminal) : maxPeopOnStop(maxPeople), avgPassengerT(avgPasT), avgBusTime(avgBusT), maxBus(maxCapacity), peopleOnStop(0), isTerminal(terminal){}

    void addPasanger() {
        if (peopleOnStop < maxPeopOnStop)
            peopleOnStop++;
        else
            std::cout << "Остановка переполнена, людей на остановке" << peopleOnStop << std::endl;
    }

    void busArrives() {
        int seats = rand() % (maxBus + 1);
        int peopleToB = std::min(peopleOnStop, seats);

        std::cout << "Прибыла маршрутка с " << seats << "местами" << std::endl;
        std::cout << "Село " << peopleToB << "человек" << std::endl;

        peopleOnStop -= peopleToB;
        std::cout << "Осталось пассажиров на остановке: " << peopleOnStop << std::endl;
    }

    int getPeopleOnStop() {
        return peopleOnStop;
    }

    void simulate(double simulationTime) {
        double currentTime = 0.0;
        double nextPasT = generateRandomTime(avgPassengerT);
        double nextBusT = generateRandomTime(avgBusTime);

        while (currentTime < simulationTime) {
            if (nextPasT <= nextBusT) {
                currentTime = nextPasT;
                std::cout << "Время: " << currentTime << " - Появился новый пассажир" << std::endl;
                addPasanger();
                nextPasT = currentTime + generateRandomTime(avgPassengerT);
            }
            else {
                currentTime = nextBusT;
                std::cout << "Время:" << currentTime << " - Прибыла маршрутка" << std::endl;
                busArrives();
                nextBusT = currentTime + generateRandomTime(avgBusTime);
            }
        }
    }

};



int main()
{
    srand(time(0));

    setlocale(LC_ALL, "Ru");
    

    int maxPeopleOnStop{};
    double avgPassengerT{}, avgBusTime{};
    int maxBus{};
    bool isTerminal;

    std::cout << "Введите максимальное кол-во людей на остановке: ";
    std::cin >> maxPeopleOnStop;

    std::cout << "Введите среднее время между появлениями пассажиров(в минутах): ";
    std::cin >> avgPassengerT;

    std::cout << "Введите среднее время между появлениями маршруток(в минутах): ";
    std::cin >> avgBusTime;

    std::cout << "Введите максимальную вместимость маршрутки: ";
    std::cin >> maxBus;

    std::cout << "Остановка конечная?(1-да, 0-нет) ";
    std::cin >> isTerminal;

    bus Bus(maxPeopleOnStop, avgPassengerT, avgBusTime, maxBus, isTerminal);

    double simulationTime = 120.0;
    Bus.simulate(simulationTime);
}
