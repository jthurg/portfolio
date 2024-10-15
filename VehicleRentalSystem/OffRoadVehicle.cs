public abstract class OffRoadVehicle : Vehicle
{
    //Define member variables.
    protected int _hours = 0;
    protected string _trailerNumber = "";

    //Define constructor.
    public OffRoadVehicle(string year, string color, string make, string model, int rentalRate, int hours, string trailerNumber) : base(year, color, make, model, rentalRate)
    {
        _hours = hours;
        _trailerNumber = trailerNumber;
    }

    //Define methods.
    public override int Return()
    {
        //Caculate and return the cost of returning the vehicle.
        int cost = (GetRentalRate() * _hours);
        return cost;
    }

    public void SetHours(int hours)
    {
        //Set the hours.
        _hours = hours;
    }

    public string GetTrailerNumber()
    {
        //Return the trailer number.
        return _trailerNumber;
    }
}