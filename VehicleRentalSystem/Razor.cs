public class Razor : OffRoadVehicle
{
    //Define member variables.
    private bool _hasWinch = false;

    //Define constructor.
    public Razor(string year, string color, string make, string model, int rentalRate, int hours, string trailerNumber, bool hasWinch) : base(year, color, make, model, rentalRate, hours, trailerNumber)
    {
        _hasWinch = hasWinch;

    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information depending on if it has a winch.
        if (_hasWinch == true)
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/hour, Has Winch: Yes");
        }
        
        else
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/hour, Has Winch: No");
        }
    }
}