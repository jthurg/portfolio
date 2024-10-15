public class Truck : OnRoadVehicle
{
    //Define member variables.
    private bool _has4WD = false;
    private string _towingCapacity = "";

    //Define constructor.
    public Truck(string year, string color, string make, string model, int rentalRate, int miles, string seats, bool has4WD, string towingCapacity) : base(year, color, make, model, rentalRate, miles, seats)
    {
        _has4WD = has4WD;
        _towingCapacity = towingCapacity;
    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information depending on if it is 4WD or 2WD.
        if (_has4WD == true)
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/mile, Seats: {_seats}, 4WD, Tow Capacity: {_towingCapacity} lbs");
        }

        else
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/mile, Seats: {_seats}, 2WD, Tow Capacity: {_towingCapacity} lbs");
        }
    }
}