import React from 'react';
import { View } from 'react-native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Icon from 'react-native-vector-icons/Ionicons';
import HomeScreen from '../screens/HomeScreen';
import Booking from '../screens/Booking';
import Map from '../screens/Map';
import BookingButton from '../components/BookingButton';
import { useTheme } from '../theme/ThemeContext';
import Login from '../screens/Login';
import LogoScreen from '../screens/LogoScreen';
// import Rooms from '../screens/Rooms';

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
                    else if (route.name === 'Map') iconName = focused ? 'map' : 'map-outline';
                    else if (route.name === 'Booking') return null;

                    return (
                        <View
                            style={{
                                backgroundColor: '#f6f8c4',
                                borderRadius: 25,
                                padding: 10,
                                alignItems: 'center',
                                justifyContent: 'center',
                                fontFamily: "Nunito",
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
            <Tab.Screen name="LogoScreen" component={LogoScreen} />
            <Tab.Screen name="Home" component={HomeScreen} />
            <Tab.Screen
                name="Booking"
                component={Booking}
                options={{
                    tabBarButton: (props) => <BookingButton {...props} />,
                }}
            />
            <Tab.Screen name="Map" component={Map} />
            <Tab.Screen name="Login" component={Login} />

        </Tab.Navigator>
    );
}
