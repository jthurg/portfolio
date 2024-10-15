public class Boat : OffRoadVehicle
{
    //Define member variables.
    private string _type = "";

    //Define constructor.
    public Boat(string year, string color, string make, string model, int rentalRate, int hours, string trailerNumber, string type) : base(year, color, make, model, rentalRate, hours, trailerNumber)
    {
        _type = type;

    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information including the boat type.
        Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/hour, Type: {_type}");
    }
}