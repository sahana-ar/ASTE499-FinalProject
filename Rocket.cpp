#include <iostream>
#include <iomanip>
#include <vector> 
#include <valarray>
#include <map>
#include <string>
#include <utility>
#include <regex>
#include <functional>
#include <sstream>
#include <iterator>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <ctype.h>
#include "json/value.h"
#include "json/json.h"
#include <boost/thread.hpp>
#include <boost/filesystem/path.hpp>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <queue>
#include <random>


using namespace std;
/// The Rocket class is used to calculate rocket performance parameters.
/// 
/// This class calculates an optimal thrust and specific impulse based off of the inputted rocket nozzle parameters.
class Rocket{
     
    /// This class is used to initialize conditions
    ///
    /// Parameters are pulled from an input file
    /// @param acceleration Acceleration of the launch vehicle
    /// @param velocity Velocity of the launch vehicle
    /// @param altitude Altitude of the launch vehicle
    /// @param thrust Thrust of the rocket engine
    /// @param Isp Specific impulse of the rocket engine
    /// @param combustionpressure Combustion pressure of the rocket nozzle
    /// @param rocketmass The mass of the rocket
    /// @param enginemass The mass of the engine
    /// @param propmass The mass of the propellant
    /// @param density Fuel density in the nozzle of the rocket engine
    /// @param thrustdura Thrust firing duration
    /// @param time Time of rocket engine burn
    /// @param exitarea Exit area of the rocket nozzle
    /// @param evel Exit velocity of the rocket nozzle
    /// @param thru Thrust of the nozzle
    /// @param acc Nozzle acceleration
    /// @param gasconst Gas constant of given fuel

    public:

        // default construct
        Rocket() {}

        // prototype of constructor for class Rocket
        // initialized data members
        Rocket(double, double, double, double, double, 
        int, double, double, double);

        double acceleration();
        double velocity();
        double altitude();
        double thrust(); 
        double Isp();

    private:

        double combustionpressure;
        double rocketmass;
        double enginemass;
        double propmass;
        double density;
        double thrustdura;
        int time;
        double exitarea;
        double evel;
        double thru;
        double acc;
        double gasconst;
};

Rocket::Rocket(double rmass, double emass, double pmass,
double den, double dura, int t, double Ae, double compress,
double R)
{
    rocketmass = rmass;
    enginemass = emass;
    propmass = pmass;
    density = den;
    thrustdura = dura;
    time = t;
    exitarea = Ae;
    combustionpressure = compress;
    gasconst = R;

}

// calculate a thrust of the rocket at the moment
double Rocket::thrust()
{
    /// This code calculates the exit velocity and thrust of the rocket
    ///
    /// Calculates thrust and exit velocity usinig the propellant mass, thrust duration, density, and exit area.
    /// @param evel Exit velocity
    /// @param thru Thrust
    
    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;

    return(thru);
}

// calculate a specific impulse of the rocket
double Rocket::Isp()
{
    /// This code calculates the Specific impulse of the rocket
    ///
    /// Calculates the velocity of the thruster and the thrust of the engine which gives the specific impulse of the rocket
    /// @param evel Exit velocity of the thruster
    /// @param thru Thrust of the engine
    /// @param isp Specific impulse

    double isp;

    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;
    // calculates a specific impulse of the rocket
    isp = (thru/(propmass/thrustdura))/9.80655;

    return (isp);
}

// calculate an acceleration of the rocket
double Rocket::acceleration()
{
    /// This code calculates the acceleration of the rocket
    ///
    /// Calculates the exit velicity, thrust and total mass which gives the acceleration of the rocket
    /// @param totmass Total mass of the launch vehicle
    /// @param acc acceleration of the rocket

    double totmass;

    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;

    // calculates the total mass
    totmass = rocketmass - (propmass/thrustdura) * time;

    // calculates the acceleration of the rocket
    acc = (thru/totmass) - 9.80655;

    return(acc);
}

// calculate a velocity of the rocket at the moment
double Rocket::velocity()
{
   /// This code calculates the velocity of the rocket at the moment
   ///
   /// Calculates exit velocity of the thruster, thrust of the engine, and total mass and acceleration of the rocket, which gives rocket velocity
   /// @param velocity Velocity of the rocket at the moment

    double vel[time];
    double totmass[time];
    double acct[time];
    double sum = 0;

    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;

    // calculates the total mass and the acceleration of the rocket
    for (int i=0;i<time;i++)
    {
        totmass[i] = rocketmass - (propmass/thrustdura) * i;
        acct[i] = (thru/totmass[i]) - 9.80655;
    }

    // calculate a velocity of the rocket
    for (int i=0;i<time;i++)
    {
        vel[i] = acct[i]*i;
        sum += vel[i];
    }

    return(sum);
}

// calculate an altitude of the rocket
double Rocket::altitude()
{
    /// This code calculates the altitude of the rocket
    ///
    /// Calculates exit velocity of the thruster, thrust of the engine, total mass and acceleration of the rocket, which gives the altitude of the rocket.
    /// @param altitude Altitude of the rocket
    
    double totheight = 0;
    double height[time];
    double vel[time];
    double totmass[time];
    double acct[time];

    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;

    // calculates the total mass and the acceleration of the rocket
    for (int i=0;i<time;i++)
    {
        totmass[i] = rocketmass - (propmass/thrustdura) * i;
        acct[i] = (thru/totmass[i]) - 9.80655;
    }

    // calculate a velocity of the rocket
    for (int i=0;i<time;i++)
    {
        vel[i] = acct[i]*i;
    }

    // calculates the altitude of the rocket
    for (int i=0;i<time;i++)
    {
        height[i] = vel[i]*i;
        totheight += height[i];
    }
    return(totheight);

}

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

vector<double> range(double min, double max, size_t N) {
    vector<double> range;
    double delta = (max-min)/double(N-1);
    for(int i=0; i<N; i++) {
        range.push_back(min + i*delta);
    }
    return range;
}

vector<vector<double>> cartesian( vector<vector<double> >& v ) {
  vector<vector<double>> results;
  auto product = []( long long a, vector<double>& b ) { return a*b.size(); };
  const long long N = accumulate( v.begin(), v.end(), 1LL, product );
  vector<double> u(v.size());
  for( long long n=0 ; n<N ; ++n ) {
    lldiv_t q { n, 0 };
    for( long long i=v.size()-1 ; 0<=i ; --i ) {
      q = div( q.quot, v[i].size() );
      u[i] = v[i][q.rem];
    }

    
      results.push_back(u);
  }
  return results;
}

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}


int main() {
    /// This function sweeps through different parameters to find the optimal solution
    /// 
    /// The sweeping function sweeps through different values of 3 different parameters. The optimized Thrust, Isp, and acceleration are then outputted.
    std::string rocketJSONPath = "Input_File.json";
    std::ifstream rocketStream(rocketJSONPath);
    Json::Value Input_File;
    rocketStream >> Input_File;

    std::string outputFolderString = "Output";
    auto outputFolderPath = boost::filesystem::system_complete(outputFolderString);
    
    //Delete existing output folder contents
    if (boost::filesystem::exists(outputFolderPath)){
        boost::filesystem::remove_all(outputFolderPath);
    }
    boost::filesystem::create_directories(outputFolderPath);

    std::vector<Json::Value*> rockets;
    rockets.push_back(&Input_File);

    vector<string> sweepJsonNames;
    std::stringstream foldername;
    foldername << "Nominal_Run";
    sweepJsonNames.push_back(foldername.str());

    /// creates field for output folder name for nominal case
    (*(rockets[0]))["output_folder"] = sweepJsonNames[0];

    /// creates output directory for nominal case
    auto outputSweepFolderPath = outputFolderPath / (*(rockets[0]))["output_folder"].asString();
    boost::filesystem::create_directories(outputSweepFolderPath);

    /// push json object back into corresponding sweep run folder
    std::stringstream sweepname;
    sweepname << (*(rockets[0]))["output_folder"] << Input_File["name"].asString() << ".json";
    auto newSweepJsonFilePath = outputSweepFolderPath / sweepname.str();
    std::ofstream sweep_json(newSweepJsonFilePath.string());
    sweep_json << Input_File << std::endl;

    vector<vector<double>> params;
    vector<vector<double>> array;
    vector<double> values{0,0,0};

    int num = Input_File["sweep"].size();

    for (int i = 0; i < num; i++) {
        for (int j = 0; j<3; j++){
            double value = Input_File["sweep"][i]["value"][j].asDouble();
            values[j] = value;
        }
        array.push_back(values);
    }
    /// creates arrays of the parameters
    for (int i = 0; i < num; i++) {
        double min = array[i][0];
        double max = array[i][1];
        int N = array[i][2];
        auto paramX = range(min, max, N);
        params.push_back(paramX);
    }
    /// computes the cartesian product of the
    auto parametersFull = cartesian(params);

    vector<vector<string>> parameterNames;
    for (int i = 0; i < num; i++) {
        std::string s = Input_File["sweep"][i]["field"].asString();
        std::string delimiter = ".";
        auto parameterX = split(s, delimiter);
        parameterNames.push_back(parameterX);
    }

    /// puts cartesian product values back into the json and prints updated object values to validate
    ///
    
    //auto rocket = nominalRocket;
    for (int numSweep = 0; numSweep<parametersFull.size(); numSweep++){
        rockets.push_back(new Json::Value(Input_File));
        for (int j=0; j<parametersFull[0].size(); j++){
            Json::Value* current = rockets.back();
               for (std::string param : parameterNames[j]) {
                   if (isNumber(param)) {
                    int number = stoi(param);
                       current = &(*current)[number];
                       continue;
                }
                current = &(*current)[param];
            }
            *current = parametersFull[numSweep][j];
        }

        /// pushes to vector of folder names and creates field in corresponding json object
        std::stringstream foldername;
        foldername << "Sweep_" << Input_File["name"].asString() << "[";
        for (int k = 0; k<parametersFull[0].size(); k++) foldername << parametersFull[numSweep][k] << ", ";
        foldername << "]";
        sweepJsonNames.push_back(foldername.str());
        (*(rockets[numSweep+1]))["output_folder"] = sweepJsonNames[numSweep+1];

        /// creates output folder for each sweep
        auto outputSweepFolderPath = outputFolderPath / sweepJsonNames.back();
        boost::filesystem::create_directories(outputSweepFolderPath);


        /// push json object back into corresponding sweep run folder
        std::stringstream sweepname;
        sweepname << (*(rockets[numSweep+1]))["output_folder"];
        auto newSweepJsonFilePath = outputSweepFolderPath / sweepname.str();
        std::ofstream sweep_json(newSweepJsonFilePath.string());
        sweep_json << *rockets.back() << std::endl;
    }




    for (auto Input_File : rockets) {

        std::ofstream myFile((*Input_File)["output_folder"].asString());
        myFile << "acceleration, velocity, altitude, thrust, Isp\n";



        double rmass = (*Input_File)["LaunchVehicle1"]["InitialMass"].asDouble();
        double emass = (*Input_File)["LaunchVehicle1"]["EngineMass"].asDouble();
        double pmass = (*Input_File)["LaunchVehicle1"]["PropelantMass"].asDouble();
        double den = (*Input_File)["LaunchVehicle1"]["Density"].asDouble();
        double dura = (*Input_File)["LaunchVehicle1"]["ThrustDuration"].asDouble(); //need this in input file
        double t = (*Input_File)["LaunchVehicle1"]["Time"].asDouble(); //need this in input file
        double Ae = (*Input_File)["LaunchVehicle1"]["NozzleExitArea"].asDouble();
        double compress = (*Input_File)["LaunchVehicle1"]["CombustionPressure"].asDouble(); //need this in input file
        double R = (*Input_File)["ChemicalProperties"]["H2GasConstant"].asDouble(); //which one?

        for (int i = 0; i < t; i++) {
        Rocket rocket(rmass, emass, pmass, den, dura, i, Ae, compress, R);
        myFile << rocket.acceleration();
        myFile << rocket.velocity();
        myFile << rocket.altitude();
        myFile << rocket.thrust(); 
        myFile << rocket.Isp() << "\n";
        }
    }

    return 0;

}