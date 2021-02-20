﻿using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media.Animation;
using System.Windows.Controls;
using Newtonsoft.Json;
using System.ComponentModel;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for JoinRoomsWindow.xaml
    /// </summary>
    public partial class JoinRoomsWindow : Window
    {
        private Dictionary<string, Room> allRooms = new Dictionary<string, Room>();

        // C'tor
        public JoinRoomsWindow()
        {
            InitializeComponent();
            Join_Button.IsEnabled = false;
            Refresh();
        }
        
        /// <summary>
        /// the func refresh the rooms data
        /// </summary>
        private void Refresh()
        {
            // define vars
            RoomsList.Items.Clear();
            allRooms.Clear();

            // hide the users in rooms
            User_Label.Visibility = Visibility.Hidden;
            PlayerList.Visibility = Visibility.Hidden;

            // create msg
            string jsonString = "{\"status\": 7}";
            byte[] arr = Helper.SerializeMsg(jsonString,7);

            // send msg
            Communicator.SendMsg(arr, arr.Length);
            KeyValuePair<int, string> msg = Communicator.GetMsg();

            // get room list
            var mainResJson = JsonConvert.DeserializeObject<Dictionary<string, object>>(msg.Value);
            var v = mainResJson["rooms"].ToString();            
            var roomResJson = JsonConvert.DeserializeObject<Dictionary<string, object>>(v); // get rooms 

            // there no rooms
            if (roomResJson == null)
            {
                // show error label
                this.ErrorLabel.Visibility = Visibility.Visible;
                Storyboard sb = Resources["sbHideAnimation"] as Storyboard;
                sb.Begin(ErrorLabel);
            }
            else
            {
                // for all the rooms
                foreach (var i in roomResJson.Keys)
                {
                    // add room to list of names and to list of rooms
                    Room room = new Room();
                    // get room json
                    var res = JsonConvert.DeserializeObject<Dictionary<string, string>>(roomResJson[i].ToString());
                    // get room info
                    room.Id =  Convert.ToUInt32(res["ID"]);
                    room.Name =res["name"];
                    room.TimePerQuestion = Convert.ToUInt32(res["timePerQuestion"]);
                    room.Num_of_question = Convert.ToUInt32(res["numOfQustion"]);
                    room.MsxPlayers = Convert.ToUInt32(res["maxPlayers"]);

                    // add to lists
                    allRooms.Add(room.Name, room);
                    this.RoomsList.Items.Add(room.Name);
                }
            }

        }

        /// <summary>
        /// the user click on the refresh button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Refresh_Button_Click(object sender, RoutedEventArgs e)
        {
            Refresh();
        }

        /// <summary>
        /// the user click on the back button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            //the func close the curr window and open the main window
            MainWindow mainWindow = new MainWindow();
            Communicator.EndCommunicate = false;
            this.Close();
            mainWindow.Show();
        }

        /// <summary>
        /// the user click on one room in the list
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Join_Button.IsEnabled = true;
            // show the players in the room
            if (RoomsList.Items.Count > 0)
            {
                // show users in room and 
                User_Label.Visibility = Visibility.Visible;
                PlayerList.Visibility = Visibility.Visible;

                // get the players
                // create msg
                Dictionary<string, int> json = new Dictionary<string, int>();

                // make json
                json.Add("roomId", (int)allRooms[RoomsList.SelectedItem.ToString()].Id);
                string jsonString = JsonConvert.SerializeObject(json);

                // make json to bytes
                byte[] arr = Helper.SerializeMsg(jsonString, 3);

                // send msg and get res
                Communicator.SendMsg(arr, arr.Length);
                KeyValuePair<int, string> msg = Communicator.GetMsg();

                // get all players json
                var v = JsonConvert.DeserializeObject<Dictionary<string, string[]>>(msg.Value);

                //add to player list each name
                foreach (var i in v["players"])
                {
                    PlayerList.Items.Add(i);
                }
            }
        }

        //the user click 'close'
        private void Window_Closing(object sender, CancelEventArgs e)
        {
            //stop the default closing
            e.Cancel = true;

            //return to main window
            Communicator.Finish();

            //close curr window
            e.Cancel = false;
        }

        private void Join_Button_Click(object sender, RoutedEventArgs e)
        {
            //create msg
            Dictionary<string, object> json = new Dictionary<string, object>();

            // make json
            json.Add("roomId", (int)allRooms[RoomsList.SelectedItem.ToString()].Id);
            json.Add("name", User.Username);
            string jsonString = JsonConvert.SerializeObject(json);
            byte[] arr = Helper.SerializeMsg(jsonString, 4);

            // send and get
            Communicator.SendMsg(arr, arr.Length);
            KeyValuePair<int, string> msg = Communicator.GetMsg();
            var v = JsonConvert.DeserializeObject<Dictionary<string, string>>(msg.Value);
            // get from the room list the selected room and save him

            if (v["status"] != "100")
            {
                User.UserRoom = allRooms[RoomsList.SelectedItem.ToString()];

                // close this window and open the room data window
                RoomDataWinow dataWinow = new RoomDataWinow();
                Communicator.EndCommunicate = false;
                Close();
                dataWinow.Show();
            }
            else
            {
                ErrorLabel.Content = "room is full...";
                ErrorLabel.Visibility = Visibility.Visible;
            }

        }
    }
}
