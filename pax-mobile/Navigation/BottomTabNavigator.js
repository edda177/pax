import React from "react";
import { View } from "react-native";
import { createBottomTabNavigator } from "@react-navigation/bottom-tabs";
import { MaterialCommunityIcons, FontAwesome6 } from "@expo/vector-icons";
import HomeScreen from "../screens/HomeScreen";
import Booking from "../screens/Booking";
import BookingButton from "../components/BookingButton";
import Contact from "../screens/Contact";
import { useTheme } from "../theme/ThemeContext";
import LoginScreen from "../screens/LoginScreen";
import Icon from "react-native-vector-icons/FontAwesome5";
import { AntDesign } from "@expo/vector-icons";
import { useAuth } from "../context/AuthContext";

// const {token} = useAuth();
const fakeToken = false;
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

          if (route.name === "Home") iconName = "home";
          else if (route.name === "Contact") iconName = "envelope";
          else if (route.name === "Login") iconName = "sign-out-alt";
          else if (route.name === "Booking") return null;

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

      <Tab.Screen
        name="Booking"
        component={Booking}
        options={{
          tabBarButton: (props) => <BookingButton {...props} />,
        }}
      />

      <Tab.Screen name="Login" component={LoginScreen} />
      {fakeToken && (
        <>
          <Tab.Screen name="Contact" component={Contact} />
        </>
      )}
      {/* <Tab.Screen name="Contact" component={Contact} /> */}
    </Tab.Navigator>
  );
}

