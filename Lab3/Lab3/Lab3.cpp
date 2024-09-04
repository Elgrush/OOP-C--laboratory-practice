//Вариант 8
#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <random>
#include <math.h>
#include <numbers>

using namespace std;

class Weatherwatcher { //abstract
public:
    enum class Type { Weathercock, Meteostation };
    enum class Field { windDirection, windSpeed, temperature, pressure };

    Weatherwatcher() {
        this->windDirection = 0;
        this->windSpeed = 0;
    }

    Weatherwatcher(double windDirection, double windSpeed) {
        setWindSpeed(windSpeed);
        setWindDirection(windDirection);
    };


    Weatherwatcher(const Weatherwatcher& anotherWeatherwatcher) {
        this->windDirection = anotherWeatherwatcher.windDirection;
        this->windSpeed = anotherWeatherwatcher.windSpeed;
    };

    virtual const Type id() const = 0;
    /// <summary>
    /// Returns the wind direction
    /// </summary>
    /// <returns>Double between 0 and 360</returns>
    double getWindDirection() const {
        return windDirection;
    }

    /// <summary>
    /// Sets wind direction
    /// </summary>
    /// <param name="windDirection">
    /// Sets wind direction between 0 and 360 degrees
    /// </param>
    void setWindDirection(double windDirection) {
        if (windDirection >= 0 && windDirection < 360)
            this->windDirection = windDirection;
        else {
            this->windDirection = 0;
            cout <<
                "Unrecognisable data, wind direction set to zero degrees"
                << endl;
        }
    }

    /// <summary>
    /// Returns the wind speed
    /// </summary>
    /// <returns>Non negative double</returns>
    double getWindSpeed() const {
        return windSpeed;
    }

    /// <summary>
    /// Sets wind speed
    /// </summary>
    /// <param name="windSpeed">Sets wind speed to non negative value
    /// </param>
    void setWindSpeed(double windSpeed) {
        if (windSpeed >= 0)
            this->windSpeed = windSpeed;
        else {
            this->windSpeed = 0;
            cout << "Unrecognisable data, wind speed set to zero" << endl;
        }
    }


    virtual ~Weatherwatcher() {};


protected:
    double windDirection;
    double windSpeed;
};

class Weathercock : public Weatherwatcher {
public:

    /// <summary>
    /// Creates a new weathercock
    /// </summary>
    Weathercock() : Weatherwatcher() {};

    /// <summary>
    /// Creates a new weathercock
    /// </summary>
    /// <param name="windDirection">
    /// Sets wind direction between 0 and 360 degrees
    /// </param>
    /// <param name="windSpeed">Sets wind speed to non negative value</param>
    Weathercock(double windDirection, double windSpeed) :
        Weatherwatcher(windDirection, windSpeed) {};

    /// <summary>
    /// Creates a copy of the weathercock
    /// </summary>
    /// <param name="anotherWeathercock">Another weathercock</param>
    Weathercock(const Weathercock& anotherWeathercock) :
        Weatherwatcher(anotherWeathercock) {};


    /// <summary>
    /// Creates a copy of the weathercock of the another weatherwatcher
    /// </summary>
    /// <param name="anotherWeatherwatcher">Another anotherWeatherwatcher</param>
    Weathercock(const Weatherwatcher& anotherWeatherwatcher) :
        Weatherwatcher(anotherWeatherwatcher) {};

    /// <summary>
    /// Destroys a weathercock
    /// </summary>
    ~Weathercock() override {};

    const Type id() const override { return Type::Weathercock; };
};

class Meteostation : public Weatherwatcher {
public:

    /// <summary>
    /// Creates a new meteostation
    /// </summary>
    Meteostation() : Weatherwatcher() {
        this->temperature = 0;
        this->pressure = 0;
    };

    /// <summary>
    /// Creates a new meteostation
    /// </summary>
    /// <param name="windDirection">
    /// Sets wind direction between 0 and 360 degrees
    /// </param>
    /// <param name="windSpeed">Sets wind speed to non negative value</param>
    /// <param name="temperature">
    /// Sets temperature in celcius greater than or equal to -273.15
    /// </param>
    /// <param name="pressure">
    /// Sets pressure in pascal to non negative value
    /// </param>
    Meteostation(double windDirection, double windSpeed,
        double temperature, double pressure) :
        Weatherwatcher(windDirection, windSpeed) {
        setTemperature(temperature);
        setPressure(pressure);
    };

    /// <summary>
    /// Creates a copy of the meteostation
    /// </summary>
    /// <param name="anotherMeteostation">Another meteostation</param>
    Meteostation(const Meteostation& anotherMeteostation) :
        Weatherwatcher(anotherMeteostation) {
        this->temperature = anotherMeteostation.temperature;
        this->pressure = anotherMeteostation.pressure;
        this->weatherData = anotherMeteostation.weatherData;
    };

    /// <summary>
    /// Returns the temperature in celcius
    /// </summary>
    /// <returns>
    /// Double greater than or equal to -273.15
    /// </returns>
    double getTemperature() const {
        return this->temperature;
    };

    /// <summary>
    /// Sets temperature
    /// </summary>
    /// <param name="temperature">
    /// Sets temperature in celcius greater than or equal to -273.15
    /// </param>
    void setTemperature(double temperature) {
        if (temperature >= -273.15)
            this->temperature = temperature;
        else {
            this->temperature = 0;
            cout <<
                "Unrecognisable data, temperature set to zero degrees"
                << endl;
        }
    }

    /// <summary>
    /// Returns the pressure in pascal
    /// </summary>
    /// <returns>Non negative double</returns>
    double getPressure() const {
        return this->pressure;
    };

    /// <summary>
    /// Sets pressure
    /// </summary>
    /// <param name="pressure">
    /// Sets pressure in pascal to non negative value
    /// </param>
    void setPressure(double pressure) {
        if (pressure >= 0)
            this->pressure = pressure;
        else {
            this->pressure = 0;
            cout <<
                "Unrecognisable data, pressure set to zero"
                << endl;
        }
    }

    /// <summary>
    /// Returns previously recorded data
    /// </summary>
    /// <returns>Copy oh the vector that contains 4 elements double map</returns>
    vector <map<Field, double>> getWeatherData() const {
        return weatherData;
    }

    /// <summary>
    /// Adds new element for data vector
    /// </summary>
    void recordWeatherData() {
        weatherData.push_back(
            map<Field, double>({
              {Field::windDirection, windDirection},
              {Field::windSpeed, windSpeed},
              {Field::temperature, temperature},
              {Field::pressure, pressure}
                }));
    }

    /// <summary>
    /// Destroys a meteostation
    /// </summary>
    ~Meteostation() override {};

    const Type id() const override { return Type::Meteostation; };

private:
    double temperature;
    double pressure;
    vector <map<Field, double>> weatherData;
};

class RealmMap {
private:
    vector <vector<Weatherwatcher*>*> realmMap;
    int length, width, corruptionIndex;

    double interpolate(double x, double x1, double x2, double f1, double f2)
        const {
        return (x2 - x) / (x2 - x1) * f1 + (x - x1) / (x2 - x1) * f2;
    }

    double doubleInterpolate(double x, double x1, double x2,
        double y, double y1, double y2,
        double f11, double f12, double f21, double f22) const {
        return interpolate(y, y1, y2, interpolate(x, x1, x2, f11, f12),
            interpolate(x, x1, x2, f21, f22));
    }

    map<Weatherwatcher::Field, double> interpolateWind(double x, double x1, double x2,
        double y, double y1, double y2,
        const Weatherwatcher* obj11, const Weatherwatcher* obj12,
        const Weatherwatcher* obj21, const Weatherwatcher* obj22) const {
        double windComponentX11 = sin(obj11->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj11->getWindSpeed();
        double windComponentY11 = cos(obj11->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj11->getWindSpeed();
        double windComponentX12 = sin(obj12->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj12->getWindSpeed();
        double windComponentY12 = cos(obj12->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj12->getWindSpeed();
        double windComponentX21 = sin(obj21->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj21->getWindSpeed();
        double windComponentY21 = cos(obj21->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj21->getWindSpeed();
        double windComponentX22 = sin(obj22->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj22->getWindSpeed();
        double windComponentY22 = cos(obj22->getWindDirection() / 180 *
            _NUMBERS_::_Pi) * obj22->getWindSpeed();
        double speedX = doubleInterpolate(x, x1, x2,
            y, y1, y2, windComponentX11, windComponentX12, windComponentX21,
            windComponentX22);
        double speedY = doubleInterpolate(x, x1, x2,
            y, y1, y2, windComponentY11, windComponentY12, windComponentY21,
            windComponentY22);
        double speed = sqrt(pow(speedX, 2) +
            pow(speedY, 2));
        double windDirecton = asin(speedX / speed) / _NUMBERS_::_Pi * 180;
        if (windDirecton < 0) windDirecton += 360;
        return map<Weatherwatcher::Field, double>{pair<Weatherwatcher::Field,
            double>(
                Weatherwatcher::Field::windSpeed, speed
            ), pair<Weatherwatcher::Field, double>(
                Weatherwatcher::Field::windDirection, windDirecton)};
    }

public:
    /// <summary>
    /// Creates map of random Meteostations with "length" number of rows and "width" number of columns
    /// </summary>
    /// <param name="length">Number of rows</param>
    /// <param name="width">Number of columns</param>
    /// <param name="corruptionIndex">Number of Weathercocks</param>
    RealmMap(int length, int width, int corruptionIndex) {
        this->length = length;
        this->width = width;
        this->corruptionIndex = 0;
        for (int i = 0; i < length; i++) {
            vector<Weatherwatcher*>* row = new vector<Weatherwatcher*>;
            for (int j = 0; j < width; j++) {
                row->push_back(new Meteostation(
                    360 * static_cast <double> (rand()) /
                    static_cast <double> (RAND_MAX + 1),
                    10000 * static_cast <double> (rand()) /
                    static_cast <double> (RAND_MAX),
                    100 * static_cast <double> (rand()) /
                    static_cast <double> (RAND_MAX) - 50,
                    10000 * static_cast <double> (rand()) /
                    static_cast <double> (RAND_MAX)
                ));
            }
            this->realmMap.push_back(row);
        }
        this->setCorruption(corruptionIndex);
    }


    /// <summary>
    /// Creats a copy of the RealmMap
    /// </summary>
    /// <param name="realmMap">RealmMap</param>
    RealmMap(const RealmMap& realmMap) {
        this->length = realmMap.length;
        this->width = realmMap.width;
        this->corruptionIndex = realmMap.corruptionIndex;
        for (int i = 0; i < this->length; i++) {
            vector<Weatherwatcher*>* row = new vector<Weatherwatcher*>;
            for (int j = 0; j < this->width; j++) {
                const Weatherwatcher* pointer = realmMap(i, j);
                if (pointer->id() == Weatherwatcher::Type::Meteostation) {
                    const Meteostation* meteostation = static_cast<
                        const Meteostation*>(pointer);
                    row->push_back(new Meteostation(*meteostation));
                }
                if (pointer->id() == Weatherwatcher::Type::Weathercock) {
                    const Weathercock* weathercock = static_cast<
                        const Weathercock*>(pointer);
                    row->push_back(new Weathercock(*weathercock));
                }
            }
            this->realmMap.push_back(row);
        }
    }

    /// <summary>
    /// Returns the map of a square realm
    /// </summary>
    /// <param name="size">Length of the kingdom's side</param>
    /// <param name="corruptionIndex">Number of Weathercocks</param>
    RealmMap(int size, int corruptionIndex) : RealmMap(
        size, size, corruptionIndex) {};

    /// <summary>
    /// Returns constant Weatherwatcher pointer by its row and column
    /// </summary>
    /// <param name="row">Integer</param>
    /// <param name="column">Integer</param>
    /// <returns>const Weatherwatcher pointer</returns>
    const Weatherwatcher* operator()(int row, int column) const {
        return (*this->realmMap[row])[column];
    }


    /// <summary>
    /// Returns Weatherwatcher pointer by its row and column
    /// </summary>
    /// <param name="row">Integer</param>
    /// <param name="column">Integer</param>
    /// <returns>Weatherwatcher pointer</returns>
    Weatherwatcher* operator()(int row, int column) {
        return (*this->realmMap[row])[column];
    }


    /// <summary>
    /// Replaces Meteostation with Weathercock
    /// </summary>
    /// <param name="row">Integer</param>
    /// <param name="column">Integer</param>
    /// <returns>Success bool</returns>
    bool downgradeToWeathercock(int row, int column) {
        Weatherwatcher* object = this->operator()(row, column);
        if (object->id() == Weatherwatcher::Type::Meteostation) {
            (*this->realmMap[row])[column] = new Weathercock(*object);
            delete object;
            return 1;
        }
        return 0;
    }


    /// <summary>
    /// Sets number of weathercocks
    /// </summary>
    /// <param name="corruptionIndex">Number of Weathercocks</param>
    void setCorruption(int corruptionIndex) {
        if (corruptionIndex > this->length * this->width) {
            corruptionIndex = this->length * this->width;
            cout <<
                "Corruption index has excided the realm's " <<
                "square and has been downgraded to " <<
                corruptionIndex << endl;
        }
        if (corruptionIndex == this->length * this->width) {
            for (int i = 0; i < this->length; i++) {
                for (int j = 0; j < this->width; j++) {
                    downgradeToWeathercock(i, j);
                }
            }
        }
        else {
            if (corruptionIndex > this->corruptionIndex) {
                int corruptionCounter = this->corruptionIndex;
                while (corruptionCounter < corruptionIndex) {
                    int point = int(static_cast <double> (rand()) /
                        static_cast <double> (RAND_MAX) *
                        this->length * this->width);
                    if (point / this->width == length) --point;
                    if (downgradeToWeathercock(point / this->width, point % this->width)) {
                        cout << corruptionCounter << " out of" << corruptionIndex << endl;
                        ++corruptionCounter;
                    }
                }
            }
            else {
                int corruptionCounter = this->corruptionIndex;
                while (corruptionCounter > corruptionIndex) {
                    int point = int(static_cast <double> (rand()) /
                        static_cast <double> (RAND_MAX) *
                        this->width * this->width);
                    if (upgradeToMeteostation(point / this->width, point % this->width)) {
                        --corruptionCounter;
                    }
                }
            }
        }
        this->corruptionIndex = corruptionIndex;
    }


    bool upgradeToMeteostation(int row, int column) {
        Weatherwatcher* object = this->operator()(row, column);
        if (object->id() == Weatherwatcher::Type::Weathercock) {
            (*this->realmMap[row])[column] = new Meteostation(
                object->getWindDirection(),
                object->getWindSpeed(),
                100 * static_cast <double> (rand()) /
                static_cast <double> (RAND_MAX) - 50,
                10000 * static_cast <double> (rand()) /
                static_cast <double> (RAND_MAX)
            );
            delete object;
            return 1;
        }
        return 0;
    }


    ~RealmMap() {
        for (int i = 0; i < this->realmMap.size(); i++) {
            for (int j = 0; j < this->realmMap[i]->size(); j++) {
                delete (*this)(i, j);
            }
            delete this->realmMap[i];
        }
    }


    int getLength()const {
        return this->length;
    }


    int getWidth()const {
        return this->width;
    }

    /// <summary>
    /// Interpolates weathercocks
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns>Map of values</returns>
    const map<Weatherwatcher::Field, double> interpolateWeathercocks(
        double x, double y) const {
        if (x > this->width-1 || y >= this->length-1) {
            throw("Point outside the realm");
        }
        int interpolationX1, interpolationX2, interpolationY1, interpolationY2;
        if (int(x) - 1 > width) {
            interpolationX2 = int(x);
            interpolationX1 = int(x) - 1;
        }
        else {
            interpolationX2 = int(x) + 1;
            interpolationX1 = int(x);
        }
        if (int(y) - 1 > length) {
            interpolationY2 = int(y);
            interpolationY1 = int(y) - 1;
        }
        else {
            interpolationY2 = int(y) + 1;
            interpolationY1 = int(y);
        }
        if (interpolationY2 == length) {
            --interpolationY2, --interpolationY1;
        }
        if (interpolationX2 == width) {
            --interpolationX2; --interpolationX1;
        }
        map<Weatherwatcher::Field, double> data;
        const Weatherwatcher* obj11, * obj12, * obj21, * obj22;
        obj11 = (*this)(interpolationY1, interpolationX1);
        obj12 = (*this)(interpolationY1, interpolationX2);
        obj21 = (*this)(interpolationY2, interpolationX1);
        obj22 = (*this)(interpolationY2, interpolationX2);

        return interpolateWind(x, interpolationX1, interpolationX2,
            y, interpolationY1, interpolationY2,
            obj11, obj12, obj21, obj22);
    }

    /// <summary>
    /// Interpolates Meteostations
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns>Map of values</returns>
    const map<Weatherwatcher::Field, double>
        interpolateMeteostations(double x, double y) const {
        
        if (x >= this->width-1 || y >= this->length-1) {
            throw("Point outside the realm");
        }
        
        int startX2 = (int)x;
        if (startX2 == x) ++startX2;
        if (startX2 == this->width) --startX2;

        int startY2 = (int)y;
        if (startY2 == y) ++startY2;
        if (startY2 == this->length) --startY2;

        for (int interpolationX2 = startX2;
            interpolationX2 < width; interpolationX2++) {
            for (int interpolationY2 = startY2;
                interpolationY2 < length; interpolationY2++) {
                if (this->operator()(interpolationY2, interpolationX2)->id()
                    == Weatherwatcher::Type::Meteostation) {
                    for (int interpolationX1 = startX2 - 1;
                        interpolationX1 >= 0; interpolationX1--) {
                        if (this->operator()(interpolationY2,
                            interpolationX1)->id() ==
                            Weatherwatcher::Type::Meteostation) {
                            for (int interpolationY1 = startY2 - 1;
                                interpolationY1 >= 0; interpolationY1--) {
                                if (this->operator()(interpolationY1,
                                    interpolationX1)->id() ==
                                    Weatherwatcher::Type::Meteostation &&
                                    this->operator()(interpolationY1,
                                        interpolationX2)->id() ==
                                    Weatherwatcher::Type::Meteostation) {
                                    return {
                                        pair<Weatherwatcher::Field, double>
                                        (Weatherwatcher::Field::pressure,
                                            doubleInterpolate(x,
                                                interpolationX1,
                                                interpolationX2,
                                                y,interpolationY1,
                                                interpolationY2,
                                        static_cast<const Meteostation*>
                                                (this->operator()(
                                                    interpolationX1,
                                                    interpolationY2))->
                                                getPressure(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(interpolationX2,
                                                interpolationY2))->
                                                getPressure(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(interpolationX1,
                                                interpolationY1))->
                                                getPressure(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(interpolationX2,
                                                interpolationY1))->
                                                getPressure()
                                        )),
                                        pair<Weatherwatcher::Field,
                                        double>
                                        (Weatherwatcher::Field::temperature,
                                            doubleInterpolate(x,
                                                interpolationX1,
                                                interpolationX2,
                                                y, interpolationY1,
                                                interpolationY2,
                                        static_cast<const Meteostation*>
                                                (this->operator()(
                                                    interpolationX1,
                                                    interpolationY1))->
                                                getTemperature(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(interpolationX2,
                                                interpolationY1))->
                                                getTemperature(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(
                                                interpolationX1,
                                                interpolationY2))->
                                                getTemperature(),
                                        static_cast<const Meteostation*>(
                                            this->operator()(interpolationX2,
                                                interpolationY2))->
                                                getTemperature()
                                        ))
                                    };
                                }
                            }
                        }
                    }
                }
            }
        }
        throw("Interpolation failed");
    }


    /// <summary>
    /// Interpolates all possible data
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns>Map of values</returns>
    const map<Weatherwatcher::Field, double>
        interpolateAll(double x, double y) const {
        map<Weatherwatcher::Field, double> wind =
            interpolateWeathercocks(x, y);
        map<Weatherwatcher::Field, double> atmosphere =
            interpolateMeteostations(x, y);
        return map<Weatherwatcher::Field, double>{
            pair<Weatherwatcher::Field, double>(
                Weatherwatcher::Field::windDirection,
                wind[Weatherwatcher::Field::windDirection]),
                pair<Weatherwatcher::Field, double>(
                    Weatherwatcher::Field::windSpeed,
                    wind[Weatherwatcher::Field::windSpeed]),
                pair<Weatherwatcher::Field, double>(
                    Weatherwatcher::Field::pressure,
                    atmosphere[Weatherwatcher::Field::pressure]),
                pair<Weatherwatcher::Field, double>(
                    Weatherwatcher::Field::temperature,
                    atmosphere[Weatherwatcher::Field::temperature])
        };
    }
};

int main() {
    cout << "Initialisation" << endl;
    RealmMap* realmMap = new RealmMap(100, 500, 3000);
    cout << "Initialisation complete" << endl;
    cout << "Tests commensing..." << endl;
    map<Weatherwatcher::Field, double> data = realmMap->interpolateAll(0,98.5);
    assert(data[Weatherwatcher::Field::windDirection] < 360 &&
        data[Weatherwatcher::Field::windDirection] >= 0);
    assert(data[Weatherwatcher::Field::windSpeed] > 0);
    assert(data[Weatherwatcher::Field::pressure] > 0);
    assert(data[Weatherwatcher::Field::temperature] > -274);
    delete realmMap;
    cout << "Tests completed" << endl;
}
