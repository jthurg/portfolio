public class Motorcycle : OnRoadVehicle
{
    //Define member variables.
    private bool _hasSideCar = false;

    //Define constructor.
    public Motorcycle(string year, string color, string make, string model, int rentalRate, int miles, string seats, bool hasSideCar) : base(year, color, make, model, rentalRate, miles, seats)
    {
        _hasSideCar = hasSideCar;
    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information depending on if it has a sidecar.
        if (_hasSideCar == true)
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/mile, Seats: {_seats}, Has Sidecar: Yes");
        }

        else
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/mile, Seats: {_seats}, Has Sidecar: No");
        }
    }
}