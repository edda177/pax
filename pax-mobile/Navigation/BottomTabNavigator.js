import React from 'react';
import { View } from 'react-native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Icon from 'react-native-vector-icons/Ionicons';
import HomeScreen from '../screens/HomeScreen';
import Booking from '../screens/Booking';
import BookingButton from '../components/BookingButton';
import { useTheme } from '../theme/ThemeContext';
import Login from '../screens/Login';
import LoadingScreen from '../screens/LoadingScreen';
import Rooms from '../screens/Rooms';
import Contact from '../screens/Contact';
import MyBookings from '../screens/MyBookings';


const Tab = createBottomTabNavigator();

export default function BottomTabNavigator() {
    const { customTheme } = useTheme();

    return (
        <Tab.Navigator
            screenOptions={({ route }) => ({
                headerShown: false,
                tabBarShowLabel: false,
                tabBarActiveTintColor: '#7DBA6A',
                tabBarInactiveTintColor: '#24524B',
                tabBarIcon: ({ focused, color, size }) => {
                    let iconName;

                    if (route.name === 'Home') iconName = focused ? 'home' : 'home-outline';
                    else if (route.name === 'MyBookings') iconName = focused ? 'person-circle' : 'person-circle-outline';
                    else if (route.name === 'Contact') iconName = focused ? 'phone-portrait' : 'phone-portrait-outline';
                    else if (route.name === 'LoadingScreen') iconName = focused ? 'square' : 'square-outline';
                    else if (route.name === 'Login') iconName = focused ? 'log-in' : 'log-in-outline';
                    else if (route.name === 'Rooms') iconName = focused ? 'map' : 'map-outline';
                    else if (route.name === 'Booking') return null;

                    return (
                        <View
                            style={{
                                backgroundColor: '#f6f8c4',
                                borderRadius: 25,
                                padding: 10,
                                alignItems: 'center',
                                justifyContent: 'center',
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
            <Tab.Screen name="MyBookings" component={MyBookings} />
            <Tab.Screen name="Login" component={Login} />

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
