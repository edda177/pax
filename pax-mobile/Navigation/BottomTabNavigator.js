import React from 'react';
import { View } from 'react-native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Icon from 'react-native-vector-icons/Ionicons';
import HomeScreen from '../screens/HomeScreen';
import Booking from '../screens/Booking';
import Map from '../screens/Map';
import BookingButton from '../components/BookingButton';
import { useTheme } from '../theme/ThemeContext';

const Tab = createBottomTabNavigator();

export default function BottomTabNavigator() {
    const { customTheme } = useTheme();

    return (
        <Tab.Navigator
            screenOptions={({ route }) => ({
                headerShown: false,
                tabBarShowLabel: false,
                tabBarActiveTintColor: '#24524B',
                tabBarInactiveTintColor: '#999999',
                tabBarIcon: ({ focused, color, size }) => {
                    let iconName;

                    if (route.name === 'Home') iconName = focused ? 'home' : 'home-outline';
                    else if (route.name === 'Map') iconName = focused ? 'map' : 'map-outline';
                    else if (route.name === 'Booking') return null;

                    return (
                        <View
                            style={{
                                backgroundColor: '#E3FAC8',
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
                    borderTopWidth: 0, // <-- Lägg till detta
                    elevation: 0,       // <-- Android: tar bort skugga
                    shadowOpacity: 0,   // <-- iOS: tar bort skugga
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
        </Tab.Navigator>
    );
}
