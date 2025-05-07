import React from "react";
import { View, ScrollView, Pressable, Image, StyleSheet } from "react-native";
import MapComponent from '../components/MapComponent'

export default function Map() {
  return (
    <ScrollView>
    <View style={styles.container}>
      <Image
        source={require("../assets/maps/karta-pax_med-nr_textkontur.png")}
        style={styles.image}
        resizeMode="cover"/>
        <Pressable
     source={require("../assets/rooms-yellow/karta-rum_4-free.png")}
      style={styles.image2}
      resizeMode="cover"/>
      <MapComponent 
      style={styles.theRooms}/>
    </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    width: "100vw",
    minHeight: "120vh",
    marginTop: "20vh",
    flexDirection: "row",
    justifyContent: "center",
    alignItems: "center",
  },
  text: {
    fontSize: 18,
    fontWeight: "bold",
    textTransform: "uppercase",
  },
  image: {
    width: "75%",
    height: "32vh",
    position: "relative",
    zIndex: "1",
  },
  image2: {
    width: "75%",
    height: "32vh",
    position: "absolute",
    zIndex: "2",
  },
  theRooms: {
    width: "50%",
    minHeight: "20vh",
    position: "absolute",
    zIndex: "5",
  },
});
