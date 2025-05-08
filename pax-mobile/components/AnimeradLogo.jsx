import { StyleSheet, Image, Animated } from "react-native";
import React from "react";

const AnimatedLogo = ({ style }) => {
  return (
    <Animated.Image
      source={require("../assets/logo/pax_logo-17.png")}
      style={styles.image}
      resizeMode="cover"
    />
  );
  
};

export default AnimatedLogo;

const styles = StyleSheet.create({
  image: {
    width: 300,
    height: 250,
  },
});
