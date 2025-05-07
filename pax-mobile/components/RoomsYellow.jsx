import React from "react";
import { View, Image, StyleSheet } from "react-native";

const RoomsYellow = () => {
  return (
    <View>
      <Image
        source={require("../assets/rooms-yellow/karta-rum_1-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
      <Image
        source={require("../assets/rooms-yellow/karta-rum_2-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
    </View>
  );
};

export default RoomsYellow;

const styles = StyleSheet.create({
  image: {
    width: "90%",
    height: "32vh",
    position: "absolute",
    zIndex: "0",
  },
});
