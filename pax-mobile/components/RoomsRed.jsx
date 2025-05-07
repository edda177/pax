import React from "react";
import { View, Image, StyleSheet } from "react-native";

const RoomsRed = () => {
  return (
    <View>
      <Image
        source={require("../assets/rooms-red/karta-bokat-rum_1.png")}
        style={styles.image}
        resizeMode="cover"
      />
      <Image
        source={require("../assets/rooms-red/karta-bokat-rum_2.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-red/karta-bokat-rum_3.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-red/karta-bokat-rum_4.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-red/karta-bokat-rum_5.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-red/karta-bokat-rum_6.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-red/karta-bokat-rum_7.png")}
        style={styles.image}
        resizeMode="cover"
      />
    </View>
  );
};

export default RoomsRed;

const styles = StyleSheet.create({
  image: {
    width: "90%",
    height: "32vh",
    position: "absolute",
  },
});
