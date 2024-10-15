public abstract class OnRoadVehicle : Vehicle
{
    //Define member variables.
    protected int _miles = 0;
    protected string _seats = "";

    //Define constructor.
    public OnRoadVehicle(string year, string color, string make, string model, int rentalRate, int miles, string seats) : base(year, color, make, model, rentalRate)
    {
        _miles = miles;
        _seats = seats;
    }

    //Define methods.
    public override int Return()
    {
        //Caculate and return cost of returning the vehicle.
        int cost = (GetRentalRate() * _miles);
        return cost; 

    }

    public void SetMiles(int miles)
    {
        //Set the miles.
        _miles = miles;
    }
}