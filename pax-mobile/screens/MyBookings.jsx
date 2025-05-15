import React from 'react';
import { View, ScrollView, Text, useEffect, Pressable, Platform, StatusBar, Image, StyleSheet } from 'react-native';
import { SafeAreaView, SafeAreaProvider } from 'react-native-safe-area-context';
import { useTheme } from '../theme/ThemeContext';
import { MaterialCommunityIcons } from '@expo/vector-icons';
import FetchRoom from "../components/FetchRoom";

const MyBookings = () => {
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
            isDark ? "Byt till ljust tema" : "Byt till mörkt tema"
          }
          style={styles.toggleButton}
        >
          <MaterialCommunityIcons
            name={isDark ? "white-balance-sunny" : "weather-night"}
            size={30}
            color={theme.iconSwitchmode}
          />
        </Pressable>
  <Text style={styles.textTitle}>min bokning</Text>
    <View style={styles.containerImage}>
        <Text style={styles.textCentered}>Rum 2</Text>
      <Image
      source={require("../assets/screenshot-rum1.jpg")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textCentered}>
        Ett litet rum för 2-6 personer. Perfekt för enskilda samtal eller mindre möten.
        </Text>
      </View>
    <View style={styles.textContainer}>
    <Text style={styles.textFat}>
      Tillgängligt: <br/>
      Luftkvalité: <br/>
      Skärm: <br/>
      Våning: <br/>
      Platser: <br/>
      Whiteboard: <br/>
      Projektor: <br/>
      </Text>
    <Text style={styles.textSmall}>
      Ja<br/>
      5 - Optimal<br/>
      Nej<br/>
      1<br/>
      6<br/>
      Ja<br/>
      Nej<br/>
    </Text>
    </View>
      <View name="fetchbox" style={styles.textContainer}>
    <Text name="fetchtext" style={{width: "95%", padding: "6%"}}>
      <FetchRoom style={{color: "#FCFFF5", textAlign: "left"}}/>
    </Text>
    </View>
     </View>
    </SafeAreaView>
    </ScrollView>
    </SafeAreaProvider>
  )
};

export default MyBookings;

const createStyles = (theme) => 
    StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: theme.background,
    width: "100vw",
    minHeight: "150vh",
    height: "auto",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
   safeArea: {
      flex: 1,
      minHeight: "150vh",
      height: "auto",
      backgroundColor: theme.background,
      paddingTop: Platform.OS === "android" ? StatusBar.currentHeight : 0,
    },
  toggleButton: {
      position: "absolute",
      top: 20,
      left: 20,
      zIndex: 1,
      backgroundColor: "#E3FAC825",
      borderRadius: 25,
      padding: 5,
    },
  containerImage: {
    flex: 1,
    width: "90vw",
    minHeight: "50vh",
    borderRadius: "15px",
    backgroundColor: "#061a17",
    marginTop: "5%",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
    image: {
    width: "80vw",
    height: "35vh",
    padding: "2%",
    borderStyle: "solid",
    borderWidth: "4px",
    borderColor: "#FCFFF530",
},
  textContainer: {
    flex: 1,
    width: "90vw",
    minHeight: "20vh",
    borderRadius: "15px",
    backgroundColor: "#061a17",
    padding: "4%",
    marginTop: "5%",
    flexDirection: "row",
    justifyContent: "center",
    alignItems: "start",
    marginBottom: "10%",
  },
  textTitle: { 
    color: theme.textPrimary,
    fontSize: 18, 
    fontWeight: "bold", 
    textAlign: "center",
    textTransform: "uppercase",
    letterSpacing: "0.6rch",
    marginTop: "5vh",
  },
  textFat: {
    color: theme.textPrimary,
    fontSize: 14, 
    lineHeight: 18,
    fontWeight: "600",
    textAlign: "right"
  },
  textSmall: { 
    color: theme.textPrimary,
    fontSize: 14, 
    lineHeight: 18,
    fontWeight: "200",
    textAlign: "left",
    marginLeft: "2%",
  },
  textCentered: {
    fontSize: 15,
    lineHeight: 17,
    fontWeight: "200",
    textAlign: "center",
    paddingVertical: "4%",
    paddingHorizontal: "4%",
    color: theme.textPrimary,
  },
});
