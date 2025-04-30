import React from 'react';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Icon from 'react-native-vector-icons/Ionicons';
import HomeScreen from '../screens/HomeScreen';
import Booking from '../screens/Booking';
import Map from '../screens/Map';
import BookingButton from '../components/BookingButton';
import { useTheme } from '../theme/ThemeContext';
import { NavigationContainer } from '@react-navigation/native';

const Tab = createBottomTabNavigator();

export default function BottomTabNavigator() {
    const { customTheme } = useTheme();

    return (
        <Tab.Navigator
            screenOptions={({ route }) => ({
                headerShown: false,
                tabBarIcon: ({ focused, color, size }) => {
                    let iconName;

                    if (route.name === 'Home') iconName = focused ? 'home' : 'home-outline';
                    else if (route.name === 'Map') iconName = focused ? 'map' : 'map-outline';
                    else if (route.name === 'Booking') return null;

                    return <Icon name={iconName} size={size} color={color} />;
                },
                tabBarStyle: {
                    backgroundColor: customTheme.colors.tabBar,
                    paddingBottom: 0,
                    height: 60,
                },
            })}
        >
            <Tab.Screen name="Home" component={HomeScreen} />
            <Tab.Screen
                name="Booking"
                component={Booking}
                options={{
                    tabBarButton: (props) => <BookingButton {...props} />,
                    tabBarLabel: 'Booking',
                }}
            />
            <Tab.Screen name="Map" component={Map} />
        </Tab.Navigator>
    );
}
