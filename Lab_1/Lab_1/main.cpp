//Вариант 8
#include <iostream>
#include <assert.h>

using namespace std;

class Weatherwatcher {
public:
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

	virtual const string id() { return "Unidentified"; };
	/// <summary>
	/// Returns the wind direction
	/// </summary>
	/// <returns>Double between 0 and 360</returns>
	double getWindDirection() const {
		return windDirection;
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
		this->windDirection = anotherWeathercock.windDirection,
			this->windSpeed = anotherWeathercock.windSpeed;
	};

	/// <summary>
	/// Destroys a weathercock
	/// </summary>
	~Weathercock() {};

	const string id() override { return "Weathercock"; };
};

class Meteostation : Weatherwatcher {
public:
	/// <summary>
	/// Creates a new meteostation
	/// </summary>
	Meteostation() : Weatherwatcher() {};

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
	Meteostation(double windDirection, double windSpeed, double temperature, double pressure) :
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
		this->windDirection = anotherMeteostation.windDirection,
			this->windSpeed = anotherMeteostation.windSpeed,
			this->temperature = anotherMeteostation.temperature,
			this->pressure = anotherMeteostation.pressure;
	};

	/// <summary>
	/// Returns the temperature in celcius
	/// </summary>
	/// <returns>
	/// Double greater than or equal to -273.15
	/// </returns>
	double getTemperature() {
		return this->temperature;
	};

	/// <summary>
	/// Returns the pressure in pascal
	/// </summary>
	/// <returns>Non negative double</returns>
	double getPressure() {
		return this->pressure;
	}

	/// <summary>
	/// Destroys a meteostation
	/// </summary>
	~Meteostation() {};

	const string id() override { return "Meteostation"; };
private:
	double temperature;
	double pressure;
};

int main() {
	Weathercock weathercock{};
	cout << weathercock.id() << endl;
	Weathercock weathercock2(1, 1);
	cout << weathercock2.getWindDirection() << endl;
}
