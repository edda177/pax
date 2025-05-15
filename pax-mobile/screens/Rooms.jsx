import React from "react";
import { View, ScrollView, Pressable, StatusBar, Image, StyleSheet } from "react-native";
import { SafeAreaView, SafeAreaProvider } from 'react-native-safe-area-context';
import { useTheme } from '../theme/ThemeContext';
import { MaterialCommunityIcons } from '@expo/vector-icons';

const Rooms = () => {
    const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles (theme);

  return (
    <SafeAreaProvider>
      <ScrollView>
    <SafeAreaView style={styles.container}>
          <StatusBar
        barStyle={isDark ? "light-content" : "dark-content"}
        backgroundColor={theme.headerBackground}
      />
      <View>
              <Pressable
          onPress={toggleTheme}
          accessible={true}
          accessibilityRole="button"
          accessibilityLabel={
            isDark ? "Byt till ljust tema" : "Byt till mörkt tema"}
          style={styles.toggleButton}
        >
          <MaterialCommunityIcons
            name={isDark ? "white-balance-sunny" : "weather-night"}
            size={30}
            color={theme.iconSwitchmode}
          />
        </Pressable>
      <View style={styles.containerMap}>
    <Image
      source={require("../assets/maps/karta-pax_med-nr.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
    </View>
<View style={styles.containerYellowRooms}>
<Image
      source={require("../assets/rooms-yellow/karta-rum_1-free.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
    <Image
      source={require("../assets/rooms-yellow/karta-rum_2-free.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-yellow/karta-rum_3-free.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-yellow/karta-rum_4-free.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-yellow/karta-rum_5-free.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-yellow/karta-rum_6-free.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-yellow/karta-rum_7-free.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
    </View>
  <View style={styles.containerRedRooms}>
  <Image
      source={require("../assets/rooms-red/karta-bokat-rum_1.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
    <Image
      source={require("../assets/rooms-red/karta-bokat-rum_2.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-red/karta-bokat-rum_3.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-red/karta-bokat-rum_4.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-red/karta-bokat-rum_5.png")}
      style={styles.aRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-red/karta-bokat-rum_6.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
          <Image
      source={require("../assets/rooms-red/karta-bokat-rum_7.png")}
      style={styles.hiddenRoom}
      resizeMode="cover"
    />
    </View>
</View>
</SafeAreaView>
</ScrollView>
</SafeAreaProvider>

  );
}

export default Rooms;

const createStyles = (theme) => 
    StyleSheet.create({
  text: {
    fontSize: 18,
    fontWeight: "bold",
    textTransform: "uppercase",
  },
  container: {
    flex: 1,
    width: "100vw",
    minHeight: "80vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
  containerMap: {
    flex: 1,
    width: "100vw",
    minHeight: "80vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    width: "80vw",
    height: "50vh",
    position: "absolute",
    zIndex: "50",
  },
  containerRedRooms: {
    flex: 1,
    width: "100vw",
    minHeight: "80vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    width: "80vw",
    height: "50vh",
    position: "absolute",
    zIndex: "20",
  },
  containerYellowRooms: {
    flex: 1,
    width: "100vw",
    minHeight: "80vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    width: "80vw",
    height: "50vh",
    position: "absolute",
    zIndex: "30",
  },
  aRoom: {
    width: "92vw",
    height: "32vh",
    position: "absolute",
    opacity: "1.0",
    zIndex: "40",
  },
  hiddenRoom: {
    width: "92vw",
    height: "32vh",
    position: "absolute",
    opacity: "0.0",
    zIndex: "40",
  }
});
