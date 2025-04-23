import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import BottomTabNavigator from './Navigation/BottomTabNavigator';

export default function App() {
  return (
    <ThemeProvider>
    <NavigationContainer>
      <BottomTabNavigator />
    </NavigationContainer>
    </ThemeProvider>
  );
}
