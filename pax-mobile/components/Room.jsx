import React from "react";
import { View, Text, Image, StyleSheet } from "react-native";

const RoomsYellow = () => {
  return (
    <View>
        <Text style={styles.textSmaller}>Room 4.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_4-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
    </View>
  );
};

export default RoomsYellow;

const styles = StyleSheet.create({
  image: {
    width: "60%",
    height: "40vh",
  },
});