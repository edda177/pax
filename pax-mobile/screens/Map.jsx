import React from "react";
import { View, Text, Image, StyleSheet } from "react-native";

export default function Map() {
  return (
    <View style={styles.container}>
       <Image
      source={require("../assets/maps/karta_pax-13.png")}
      style={styles.image}
      resizeMode="cover"/>
        <Image
      source={require("../assets/maps/karta_pax-13.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.text}>Room map höpp</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, width: "100%", minHeight: "100vh", 
    justifyContent: "center", alignItems: "center" },
  text: { fontSize: 24, fontWeight: "bold" },
  image: {
    width: "90%", 
    height: "32vh"
}
});
