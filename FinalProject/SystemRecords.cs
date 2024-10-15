public class SystemRecords
{
    //Define member variables.
    public List<OnRoadVehicle> _onRoadVehicles = new List<OnRoadVehicle>();
    public List<OffRoadVehicle> _offRoadVehicles = new List<OffRoadVehicle>();
    private List<Vehicle> _rentalList = new List<Vehicle>();
    private List<Vehicle> _returnList = new List<Vehicle>();

    //Define constructor.
    public SystemRecords()
    {
    }

    //Define methods.
    public void DisplayOnRoadVehicles()
    {
        int count = 0;
        foreach (OnRoadVehicle vehicle in _onRoadVehicles)
        {
            //Iterate through _onRoadVehicles list to display the vehicle with its DisplayInfo method.
            count += 1;
            Console.Write($"{count}. ");
            vehicle.DisplayInfo();
            Console.WriteLine();
        }
    }

    public void DisplayOffRoadVehicles()
    {
        int count = 0;
        foreach (OffRoadVehicle vehicle in _offRoadVehicles)
        {
            //Iterate through _offRoadVehicles list to display the vehicle with its DisplayInfo method.
            count += 1;
            Console.Write($"{count}. ");
            vehicle.DisplayInfo();
            Console.WriteLine();
        }
    }

    public void AddVehicleToReturnList(Vehicle vehicle)
    {
        //Add vehicle to return list.
        _returnList.Add(vehicle);
    }

    public void AddVehicleToRentalList(Vehicle vehicle)
    {
        //Add vehicle to rental list.
        _rentalList.Add(vehicle);
    }

    public List<Vehicle> GetRentalList()
    {
        //Clear the rental list.
        _rentalList.Clear();

        //Add vehicles from OnRoad and OffRoad lists to the rental list if they are being rented.
        foreach (Vehicle vehicle in _onRoadVehicles)
        {
            if (vehicle.GetRentalStatus() == "true")
            {
                AddVehicleToRentalList(vehicle);
            }
        }

        foreach (Vehicle vehicle in _offRoadVehicles)
        {
            if (vehicle.GetRentalStatus() == "true")
            {
                AddVehicleToRentalList(vehicle);
            }
        }

        //Return the rental list.
        return _rentalList;
    } 

    public List<Vehicle> GetReturnList()
    {
        //Return the return list.
        return _returnList;
    } 
}