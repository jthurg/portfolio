public class JetSki : OffRoadVehicle
{
    //Define member variables.
    private bool _hasRoosterTail = false;

    //Define constructor.
    public JetSki(string year, string color, string make, string model, int rentalRate, int hours, string trailerNumber, bool hasRoosterTail) : base(year, color, make, model, rentalRate, hours, trailerNumber)
    {
        _hasRoosterTail = hasRoosterTail;
    }

    //Define methods.
    public override void DisplayInfo()
    {
        //Display vehicle information depending on if it has a rooster tail.
        if (_hasRoosterTail == true)
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/hour, Has Rooster Tail: Yes");
        }

        else
        {
            Console.Write($"{_year} {_color} {_make} {_model}, Rate: ${_rentalRate}/hour, Has Rooster Tail: No");
        }
    }
}