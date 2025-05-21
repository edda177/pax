import React from "react";
import { View } from "react-native";
import { createBottomTabNavigator } from "@react-navigation/bottom-tabs";
import Icon from "react-native-vector-icons/FontAwesome5";
import HomeScreen from "../screens/HomeScreen";
import Booking from "../screens/Booking";
import BookingButton from "../components/BookingButton";
import { useTheme } from "../theme/ThemeContext";
import LoadingScreen from "../screens/LoadingScreen";
import Rooms from "../screens/Rooms";
import Contact from "../screens/Contact";
import BookedScreen from "../screens/BookedScreen";
import LoginTest from "../screens/LoginScreen";

const Tab = createBottomTabNavigator();

export default function BottomTabNavigator() {
  const { customTheme } = useTheme();

  return (
    <Tab.Navigator
      screenOptions={({ route }) => ({
        headerShown: false,
        tabBarShowLabel: false,
        tabBarActiveTintColor: "rgb(228, 255, 183)",
        tabBarInactiveTintColor: "rgb(36, 82, 75)",
        tabBarIcon: ({ focused, color, size }) => {
          let iconName;

          if (route.name === "Home") iconName = focused ? "home" : "home";
          else if (route.name === "BookedScreen")
            iconName = focused ? "check-square" : "check-square";
          else if (route.name === "Login")
            iconNameHuh = focused ? "ööh?" : "ööh?";
          else if (route.name === "Booking") return null;
          else if (route.name === "LoadingScreen")
            iconNameHuh = focused ? "ööh?" : "ööh?";
          else if (route.name === "Rooms") iconName = focused ? "map" : "map";
          else if (route.name === "Contact")
            iconName = focused ? "envelope" : "envelope";

          return (
            <View
              style={{
                backgroundColor: "#84ca6f",
                borderRadius: 25,
                padding: 10,
                alignItems: "center",
                justifyContent: "center",
              }}
            >
              <Icon name={iconName} size={size} color={color} />
            </View>
          );
        },
        tabBarStyle: {
          backgroundColor: customTheme.colors.tabBar,
          paddingBottom: 0,
          paddingTop: 10,
          height: 60,
          borderTopWidth: 0,
          elevation: 0,
          shadowOpacity: 0,
        },
      })}
    >
      <Tab.Screen name="Home" component={HomeScreen} />
      <Tab.Screen name="BookedScreen" component={BookedScreen} />
      <Tab.Screen name="Login" component={LoginTest} />

      <Tab.Screen
        name="Booking"
        component={Booking}
        options={{
          tabBarButton: (props) => <BookingButton {...props} />,
        }}
      />
      <Tab.Screen name="LoadingScreen" component={LoadingScreen} />
      <Tab.Screen name="Rooms" component={Rooms} />
      <Tab.Screen name="Contact" component={Contact} />
    </Tab.Navigator>
  );
}
