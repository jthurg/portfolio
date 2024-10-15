public abstract class Vehicle
{
    //Define member variables.
    protected string _year = "";
    protected string _color = "";
    protected string _make = "";
    protected string _model = "";
    protected int _rentalRate = 0;
    protected string _isRented = "false";

    //Define constructor.
    public Vehicle(string year, string color, string make, string model, int rentalRate)
    {
        _year = year;
        _color = color;
        _make = make;
        _model = model;
        _rentalRate = rentalRate;
    }

    //Define methods.
    public string GetRentalStatus()
    {
        //Return the rental status.
        return _isRented;
    }
    
    public void Rent()
    {
        //Set the rental status to true.
        _isRented = "true";
    }

    public abstract int Return();

    public abstract void DisplayInfo();

    public int GetRentalRate()
    {
        //Return the rental rate.
        return _rentalRate;
    }
}