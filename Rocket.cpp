#include <iostream>
using namespace std;

class Rocket{
    
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
}

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
    
    // calculates an exit velocity of the thruster
    evel = (propmass/thrustdura) / (density*exitarea);
    // calculates the thrust
    thru = (propmass/thrustdura) * evel;

    return(thru);
}

// calculate a specific impulse of the rocket
double Rocket::Isp()
{
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