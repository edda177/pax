import { StyleSheet, Pressable, View } from "react-native";
import React from "react";
import RoomsYellow from "./RoomsYellow";
import RoomsRed from "./RoomsRed";

const MapComponent = () => {
  <View>
    <RoomsRed style={styles.layerOne}/>
    <RoomsYellow style={styles.layerTwo}/>
  </View>;
};

export default MapComponent;

const styles = StyleSheet.create({
    image: {
        width: "90%", 
        height: "32vh",
    },
  layerOne: {
    width: "90%",
    height: "32vh",
    position: "absolute",
    zIndex: "1",
  },
  layerTwo: {
    width: "90%",
    height: "32vh",
    position: "absolute",
    zIndex: "2",
  },
});
