public class Car : OnRoadVehicle
{
    //Define member variables.
    private string _type = "";

    //Define constructor.
    public Car(string year, string color, string make, string model, int rentalRate, int miles, string seats, string type) : base(year, color, make, model, rentalRate, miles, seats)
    {
        _type = type;
    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information.
        Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/mile, Seats: {_seats}, Type: {_type}");
    }
}