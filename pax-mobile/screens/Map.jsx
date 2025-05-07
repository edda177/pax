import React from "react";
import { View, ScrollView, Image, StyleSheet } from "react-native";
import MapComponent from '../components/MapComponent';

export default function Map() {
  return (
    <ScrollView>
    <View style={styles.container}>
      <Image
        source={require("../assets/maps/karta-pax_med-nr_textkontur.png")}
        style={styles.image}
        resizeMode="cover"/>
        {/* <Image
     source={require("../assets/rooms-yellow/karta-rum_4-free.png")}
      style={styles.image2}
      resizeMode="cover"/> */}

          <MapComponent 
      style={styles.map}
      resizeMode="cover"/>

    </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    width: "100vw",
    minHeight: "80vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
  text: {
    fontSize: 18,
    fontWeight: "bold",
    textTransform: "uppercase",
  },
  image: {
    width: "92vw",
    height: "32vh",
    position: "absolute",
    zIndex: "99",
  },
  image2: {
    width: "80vw",
    height: "32vh",
    position: "absolute",
    opacity: "0.7",
    zIndex: "2",
    borderStyle: "solid",
    broderWidth: "6px",
    borderColor: "yellow",
  },
  map: {
    backgroundColor: "#ffffff",
    width: "80vw",
    height: "50vh",
    position: "absolute",
    zIndex: "4",
  },
});
