import React from 'react';
import { View, ScrollView, Text, useEffect, Pressable, Platform, StatusBar, Image, StyleSheet } from 'react-native';
import { SafeAreaView, SafeAreaProvider } from 'react-native-safe-area-context';
import { useTheme } from '../theme/ThemeContext';
import { MaterialCommunityIcons } from '@expo/vector-icons';
import FetchRoom from "../components/FetchRoom";

const BookedScreen = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles (theme);

  return (
    <SafeAreaProvider>
    <ScrollView>
  <SafeAreaView style={styles.safeArea}>
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
  <Text style={styles.textTitle}>Paxade rum</Text>
    <View style={styles.containerImage}>
        <Text style={styles.textCentered}>Rum 2</Text>
      <Image
      source={require("../assets/screenshot-rum1.jpg")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textCentered}>
        <b>Beskrivning:</b><br/>
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
    <Text name="fetchtext" style={{width: "95vw", padding: "2em"}}>
      <FetchRoom style={{color: "#FCFFF5", textAlign: "left"}}/>
    </Text>
    </View>
     </View>
    </SafeAreaView>
    </ScrollView>
    </SafeAreaProvider>
  )
};

export default BookedScreen;

const createStyles = (theme) => 
    StyleSheet.create({
   safeArea: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: theme.background,
    paddingTop: Platform.OS === "android" ? StatusBar.currentHeight : 0,
    },
  toggleButton: {
      position: "absolute",
      top: 20,
      left: 20,
      zIndex: 1,
      backgroundColor: "#E3FAC860",
      borderRadius: 50,
    },
  containerImage: {
    flex: 1,
    width: "90vw",
    height: "30vh",
    borderRadius: "16px",
    backgroundColor: "#061a17",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
    image: {
    width: "87vw",
    height: "50vh",
    borderStyle: "solid",
    borderWidth: "6px",
    borderColor: "#FCFFF530",
},
  textContainer: {
    flex: 1,
    width: "90vw",
    minHeight: "100vh",
    borderRadius: "15px",
    backgroundColor: "#061a17",
    padding: "4%",
    marginTop: "5%",
    flexDirection: "row",
    justifyContent: "center",
    alignItems: "start",
  },
  textTitle: { 
     color: theme.textDark,
        fontFamily: "Nunito",
        fontWeight: '800',
        marginTop: 3,
        letterSpacing: "0.06rem",
        textAlign: "center",
    color: theme.textPrimary,
    fontSize: 18, 
    textTransform: "uppercase",
    letterSpacing: "0.6rch",
    marginTop: "12vh",
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
