//Вариант 8
#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;

class Weatherwatcher { //abstract
public:
	enum class Type { Weathercock, Meteostation };
	enum class Field { windDirection,windSpeed  };

	Weatherwatcher() {
		this->windDirection = 0;
		this->windSpeed = 0;
	}

	Weatherwatcher(double windDirection, double windSpeed) {
		if (windDirection >= 0 && windDirection < 360)
			this->windDirection = windDirection;
		else {
			this->windDirection = 0;
			cout <<
				"Unrecognisable data, wind direction set to zero degrees"
				<< endl;
		}
		if (windSpeed >= 0)
			this->windSpeed = windSpeed;
		else {
			this->windSpeed = 0;
			cout << "Unrecognisable data, wind speed set to zero" << endl;
		}
	};

	virtual const Type id() const = 0;
	/// <summary>
	/// Returns the wind direction
	/// </summary>
	/// <returns>Double between 0 and 360</returns>
	double getWindDirection() const {
		return windDirection;
	}

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
	Weathercock(const Weathercock& anotherWeathercock) {
		this->windDirection = anotherWeathercock.windDirection;
		this->windSpeed = anotherWeathercock.windSpeed;
	};

	/// <summary>
	/// Destroys a weathercock
	/// </summary>
	~Weathercock() {};

	const Type id() const override { return Type::Weathercock; };
};

class Meteostation : public Weatherwatcher {
public:
	enum class Field{
		temperature,
		pressure,
		windDirection,
		windSpeed
	};

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
		if (temperature >= -273.15)
			this->temperature = temperature;
		else {
			this->temperature = 0;
			cout <<
				"Unrecognisable data, temperature set to zero degrees"
				<< endl;
		}
		if (pressure >= 0)
			this->pressure = pressure;
		else {
			this->pressure = 0;
			cout <<
				"Unrecognisable data, pressure set to zero"
				<< endl;
		}
	};

	/// <summary>
	/// Creates a copy of the meteostation
	/// </summary>
	/// <param name="anotherMeteostation">Another meteostation</param>
	Meteostation(const Meteostation& anotherMeteostation) {
		this->windDirection = anotherMeteostation.windDirection;
		this->windSpeed = anotherMeteostation.windSpeed;
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
	/// Returns the pressure in pascal
	/// </summary>
	/// <returns>Non negative double</returns>
	double getPressure() const {
		return this->pressure;
	};

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
	~Meteostation() {};

	const Type id() const override { return Type::Meteostation; };
private:
	double temperature;
	double pressure;
	vector <map<Field,double>> weatherData;
};

int main() {
	cout << "Default constructor and get methods test" << endl;
	Weathercock* weathercock = new Weathercock;
	Meteostation* meteostation = new Meteostation;
	assert(weathercock->getWindDirection() == 0);
	assert(meteostation->getWindDirection() == 0);
	assert(weathercock->getWindSpeed() == 0);
	assert(meteostation->getWindSpeed() == 0);
	assert(meteostation->getTemperature() == 0);
	assert(meteostation->getPressure() == 0);
	cout << "Test completed" << endl;

	cout << "Initializer constructor test" << endl;

	delete weathercock;
	weathercock = new Weathercock(180, 3);
	delete meteostation;
	meteostation = new Meteostation(20, 30, 40, 50000);

	assert(weathercock->getWindDirection() == 180);
	assert(weathercock->getWindSpeed() == 3);
	assert(meteostation->getPressure() == 50000);
	assert(meteostation->getTemperature() == 40);
	assert(meteostation->getWindDirection() == 20);
	assert(meteostation->getWindSpeed() == 30);
	cout << "Test complete" << endl;

	cout << "Copy constructor test" << endl;
	Weathercock* weathercock2 = new Weathercock(*weathercock);
	Meteostation* meteostation2 = new Meteostation(*meteostation);
	assert(weathercock2->getWindDirection() == 180);
	assert(weathercock2->getWindSpeed() == 3);
	assert(meteostation2->getPressure() == 50000);
	assert(meteostation2->getTemperature() == 40);
	assert(meteostation2->getWindDirection() == 20);
	assert(meteostation2->getWindSpeed() == 30);
	cout << "Test complete" << endl;
	delete weathercock, delete weathercock2,
		delete meteostation, delete meteostation2;

	cout << "Identification method test:" << endl;
	weathercock = new Weathercock();
	meteostation = new Meteostation();
	assert(weathercock->id() == Weatherwatcher::Type::Weathercock);
	assert(meteostation->id() == Weatherwatcher::Type::Meteostation);
	cout << "Test complete" << endl;

	cout << "Data collection test:" << endl;
	meteostation = new Meteostation(20, 30, 40, 50000);
	meteostation->recordWeatherData();
	assert(meteostation->getWeatherData()[0][Meteostation::Field::windDirection]
		== 20);
	assert(meteostation->getWeatherData()[0][Meteostation::Field::windSpeed]
		== 30);
	assert(meteostation->getWeatherData()[0][Meteostation::Field::temperature]
		== 40);
	assert(meteostation->getWeatherData()[0][Meteostation::Field::pressure]
		== 50000);
	cout << "All tests passed" << endl;
}
