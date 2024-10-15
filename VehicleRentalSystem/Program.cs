using System;
using System.Security.Permissions;
using System.Xml.Schema;

class Program
{
    static void Main(string[] args)
    {
        //Instantiate the system records.
        SystemRecords systemRecords = new SystemRecords();

        //Instantiate all the vehicles that are available and add them to respective lists.

        //On-Road Vehicles
        Car car1 = new Car("2018", "Blue", "Toyota", "Camry", 3, 0, "4", "Sedan");
        Car car2 = new Car("2015", "Black", "Nissan", "Maxima", 3, 0, "7", "SUV");
        Truck truck1 = new Truck("2020", "Red", "Ford", "F-150", 5, 0, "5", true, "10,000");
        Truck truck2 = new Truck("2022", "White", "Chevy", "Silverado", 5, 0, "5", true, "15,000");
        Motorcycle motorcycle1 = new Motorcycle("2018", "Red", "Harley-Davidson", "Sportster", 2, 0, "2", true);
        Motorcycle motorcycle2 = new Motorcycle("2014", "Black", "Kawasaki", "Ninja", 2, 0, "1", false);

        //Add On-Road Vehicles to respective lists.
        systemRecords._onRoadVehicles.Add(car1);
        systemRecords._onRoadVehicles.Add(car2);
        systemRecords._onRoadVehicles.Add(truck1);
        systemRecords._onRoadVehicles.Add(truck2);
        systemRecords._onRoadVehicles.Add(motorcycle1);
        systemRecords._onRoadVehicles.Add(motorcycle2);

        //Off-Road Vehicles
        Razor razor1 = new Razor("2017", "Green", "Kawasaki", "Teryx", 120, 0, "21", false);
        Razor razor2 = new Razor("2015", "Black", "Polaris", "RZR", 190, 0, "22", true);
        Boat boat1 = new Boat("2013", "Blue", "Yamaha", "242 Limitless", 150, 0, "23", "Jet Boat");
        Boat boat2 = new Boat("2020", "Red", "Sun Tracker", "Party Barge DLX", 250, 0, "24", "Jet Boat");
        JetSki jetski1 = new JetSki("2019", "White", "SeaDoo", "GTR 230", 95, 0, "25", false);
        JetSki jetski2 = new JetSki("2021", "Green", "Yamaha", "WaveRunner", 125, 0, "26", true);

        //Add Off-Road Vehicles to respective lists.
        systemRecords._offRoadVehicles.Add(razor1);
        systemRecords._offRoadVehicles.Add(razor2);
        systemRecords._offRoadVehicles.Add(boat1);
        systemRecords._offRoadVehicles.Add(boat2);
        systemRecords._offRoadVehicles.Add(jetski1);
        systemRecords._offRoadVehicles.Add(jetski2);

        //Define the menu text.
        string menuText = "Main Menu:\n" +
        "   1. Rent\n" +
        "   2. Return\n" +
        "   3. Estimate Rental Cost\n" +
        "   4. View Return Cart\n" +
        "   5. Checkout\n" +
        "Please select a choice from the menu: ";

        //Define the grand total cost.
        int grandTotal = 0;

        //Display program welcome message.
        Console.WriteLine();
        Console.WriteLine("Welcome to Bob's Vehicle Rentals!");

        //Create a menu loop.
        string userChoice = "0";
        while (userChoice != "finished")
        {
            //Display menu.
            Console.Write(menuText);
            userChoice = Console.ReadLine();

            //If the user enters 1, display the rental menu.
            if (userChoice == "1")
            {
                string rentChoice = "0";
                string rentalMenuText = "Rental Menu:\n" +
                "   1. On-Road Vehicles\n" +
                "   2. Off-Road Vehicles\n" +
                "   3. Go Back\n" +
                "Please select a choice from the menu: ";

                while (rentChoice != "3")
                {
                    Console.Write(rentalMenuText);
                    rentChoice = Console.ReadLine();

                    if (rentChoice == "1")
                    {
                        //Code to display on road vehicles rental menu.
                        Console.WriteLine("Here are the on-road vehicles available for rent: ");
                        systemRecords.DisplayOnRoadVehicles();

                        //Ask user what vehicle they want to rent and call its rent method.
                        Console.Write("What on-road vehicle are you renting?: ");
                        int rentNumber = int.Parse(Console.ReadLine());
                        systemRecords._onRoadVehicles[rentNumber - 1].Rent(); 
                        
                    }

                    else if (rentChoice == "2")
                    {
                        //Code to display off-road vehicles rental menu.
                        Console.WriteLine("Here are the off-road vehicles available for rent: ");
                        systemRecords.DisplayOffRoadVehicles();

                        //Ask user what vehicle they want to rent and call its rent method.
                        Console.Write("What off-road vehicle are you renting?: ");
                        int rentNumber = int.Parse(Console.ReadLine());
                        systemRecords._offRoadVehicles[rentNumber - 1].Rent();

                    }

                    else if (rentChoice == "3")
                    {
                        //Return to the main menu by ending the rental menu loop.
                        //(No code needed).
                    }

                    else
                    {
                        //Code to display an error message.
                        Console.WriteLine("Invalid input. Please enter a number 1-3.");
                    }
                }
            }

            //If the user enters 2, display the return menu.
            else if (userChoice == "2")
            {
                string returnChoice = "0";
                string returnMenuText = "Return Menu:\n" +
                "   1. On-Road Vehicles\n" +
                "   2. Off-Road Vehicles\n" +
                "   3. Go Back\n" +
                "Please select a choice from the menu: ";

                //Code to display the return menu.
                while (returnChoice != "3")
                {
                    Console.Write(returnMenuText);
                    returnChoice = Console.ReadLine();

                    if (returnChoice == "1")
                    {
                        //Display on-road vehicles.
                        Console.WriteLine("Here are the on-road vehicles available for return: ");
                        systemRecords.DisplayOnRoadVehicles();

                        //Ask user what vehicle they want to return and how many miles they used it for.
                        Console.Write("What on-road vehicle are you returning?: ");
                        int returnNumber = int.Parse(Console.ReadLine());
                        Console.Write("How many miles did you use this vehicle for? ");
                        int miles = int.Parse(Console.ReadLine());

                        //Update the miles on the vehicle and call the vehicle's return method.
                        systemRecords._onRoadVehicles[returnNumber - 1].SetMiles(miles);
                        int returnCost = systemRecords._onRoadVehicles[returnNumber - 1].Return();
                        systemRecords.AddVehicleToReturnList(systemRecords._onRoadVehicles[returnNumber - 1]);
                        
                        //Update the transaction total cost.
                        grandTotal += returnCost;

                        //Can I avoid making the list a public member variable by RETURNING the _onRoadVehicles
                        //list instead with a method????#####################

                    }

                    else if (returnChoice == "2")
                    {
                        //Display off-road vehicles..
                        Console.WriteLine("Here are the off-road vehicles available for return: ");
                        systemRecords.DisplayOffRoadVehicles();

                        //Ask user what they want to return and how many hours they used it for.
                        Console.Write("What off-road vehicle are you returning?: ");
                        int returnNumber = int.Parse(Console.ReadLine());
                        Console.Write("How many hours did you use this vehicle for? ");
                        int hours = int.Parse(Console.ReadLine());

                        //Update the hours on the vehicle and call the vehicle's return method.
                        systemRecords._offRoadVehicles[returnNumber - 1].SetHours(hours);
                        int returnCost = systemRecords._offRoadVehicles[returnNumber - 1].Return();
                        systemRecords.AddVehicleToReturnList(systemRecords._offRoadVehicles[returnNumber - 1]);
                        
                        //Update the transaction total cost.
                        grandTotal += returnCost;
                    }

                    else if (returnChoice == "3")
                    {
                        //Code to return to the main menu.
                        //None needed.
                    }

                    else
                    {
                        //Display an error message.
                        Console.WriteLine("Invalid input. Please enter a number 1-3.");
                    }
                }
            }

            //If the user enters 3, display the potential rental items and the estimated cost.
            else if (userChoice == "3")
            {
                //Code to display the list of items in the rentalList.
                int count = 0;
                float estimatedCost = 0;
                foreach (Vehicle vehicle in systemRecords.GetRentalList())
                {
                    count += 1;
                    Console.Write($"    {count}. ");
                    vehicle.DisplayInfo();
                    Console.WriteLine();

                    //If the vehicle is an on-road vehicle, ask how many miles to get the estimated cost.
                    string objName = vehicle.GetType().BaseType.Name;
                    if (objName == "OnRoadVehicle")
                    {
                        Console.Write("How many miles do you plan on driving this vehicle? ");
                        int miles = int.Parse(Console.ReadLine());
                        estimatedCost += (vehicle.GetRentalRate() * miles);
                    }

                    //If the vehicle is an off-road vehicle, ask how many hours to get the estimated cost.
                    else 
                    {
                        Console.Write("How many hours do you plan on using this vehicle? ");
                        int hours = int.Parse(Console.ReadLine());
                        estimatedCost += (vehicle.GetRentalRate() * hours);
                    }
                }
                
                //Code to display the estimated cost.
                Console.WriteLine();
                Console.WriteLine($"Your estimated cost is: ${estimatedCost}.00");
                Console.WriteLine();
            }

            //If the user enters 4, display the items in the Return Cart, but not
            //an estimated cost like the rental list.
            else if (userChoice == "4")
            {
                //
                if (systemRecords.GetReturnList().Count == 0)
                {
                    //Display message if the return list is empty.
                    Console.WriteLine("The return list is currently empty.");
                }

                else
                {
                    //Code to display the list of items in the returnList.
                    int count = 0;
                    foreach (Vehicle vehicle in systemRecords.GetReturnList())
                    {
                        count += 1;
                        Console.Write($"    {count}. ");
                        vehicle.DisplayInfo();
                        Console.WriteLine();
                    }  
                }

                //Spacing.
                Console.WriteLine();
            }

            //If the user enters 5, execute the checkout function and then end the program.
            else if (userChoice == "5")
            {
                //Code if there is a checkout cost to be paid.
                if (grandTotal > 0)
                {
                    bool checkout = true;
                    int change = 0;
                    while (checkout == true)
                    {
                        //Code for the transaction if there is a checkout cost to be paid.
                        Console.WriteLine($"Your total cost is: ${grandTotal}.00");
                        Console.WriteLine();
                        Console.Write("Enter the payment amount (whole bills only): ");
                        int payment = int.Parse(Console.ReadLine());
                        grandTotal = grandTotal - payment;
                        if (grandTotal > 0)
                        {
                            //If the payment is insufficient, display an error message.
                            Console.WriteLine("Insufficient funds. Add more payment.");
                        }
                        
                        else if (grandTotal == 0)
                        {
                            //If the payment is sufficient, end the checkout loop.
                            change = 0;
                            checkout = false;
                        }

                        else 
                        {
                            //If the payment is more than sufficient, determine the change and end the checkout loop.
                            change = -1 *grandTotal;
                            checkout = false;
                        }
                    }
                    
                    //Display change after successful payment.
                    Console.WriteLine($"Thank you! Your change is ${change}.00.");
                }

                else
                {
                    //Display a message if there is no checkout cost to be paid.
                    Console.WriteLine("You have no payment due.");
                }

                //End system menu loop.
                userChoice = "finished";
            }

            //If the user enters anything other than 1, 2, 3, 4, or 5 in main menu,
            //then display an error message.
            else
            {
                Console.WriteLine("Invalid input. Please enter a number 1-5.");
            }
        }

        //Make a temporary list of vehicles that have trailers from the rental list.
        List<OffRoadVehicle> trailerVehiclesList = new List<OffRoadVehicle>{};
        foreach (Vehicle vehicle in systemRecords.GetRentalList())
        {
            if(vehicle.GetType().BaseType.Name == "OffRoadVehicle")
            {
                //Add the vehicle to the temporary list if it has a trailer.
                trailerVehiclesList.Add((OffRoadVehicle)vehicle);
            }
        }

        //If there are vehicless on the temporary list, display their respective trailer numbers.
        if(trailerVehiclesList.Count > 0)
        {
            //Code to display what trailers the user will be picking up if
            //renting something with a trailer.
            Console.WriteLine("You will be picking up these trailers for your rentals: ");

            foreach(OffRoadVehicle offVehicle in trailerVehiclesList)
            {
                //Display trailer numbers.
                Console.WriteLine(offVehicle.GetTrailerNumber());
            }
        }

        //Display end program message.
        Console.WriteLine();
        Console.WriteLine("Thank you for using the Vehicle Rental System at Bob's Vehicle Rentals. Goodbye!");
        
        //End spacing.
        Console.WriteLine();
    }
}