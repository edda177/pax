import React from 'react';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Icon from 'react-native-vector-icons/Ionicons';
import ThemeToggleScreen from '../screens/ThemeToggleScreen';
import HomeScreen from '../screens/HomeScreen';
import Booking from '../screens/Booking';
import Map from '../screens/Map';
import ThemeToggleTabButton from '../components/ThemeToggleTabButton';
import BookingButton from '../components/BookingButton';
import { useTheme } from '../theme/ThemeContext';
import { NavigationContainer } from '@react-navigation/native';

const Tab = createBottomTabNavigator();

export default function BottomTabNavigator() {
    const {customTheme} = useTheme();

    return (
        <Tab.Navigator
            screenOptions={({ route }) => ({
                headerShown: false,
                tabBarIcon: ({ focused, color, size }) => {
                    if (route.name === 'Booking') return null;

                    let iconName;
                    if (route.name === 'Home') iconName = focused ? 'home' : 'home-outline';
                    else if (route.name === 'Map') iconName = focused ? 'map' : 'map-outline';

                    return <Icon name={iconName} size={size} color={color} />;
                },
                    tabBarStyle: {
                        backgroundColor: customTheme.colors.tabBar,
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
            <Tab.Screen name="Map" component={Map} />
            <Tab.Screen
                name="Theme"
                component={ThemeToggleScreen}
                options={{
                    tabBarIcon: ({ color, size }) => (
                        <MaterialCommunityIcons
                            name={isDark ? "white-balance-sunny" : "weather-night"}
                            color={color}
                            size={size}
                        />
                    ),
                    tabBarLabel: "Tema",
                    tabBarButton: (props) => <ThemeToggleTabButton {...props} />,
                }}
            />
        </Tab.Navigator>
    );
}
