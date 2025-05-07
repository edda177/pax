import { StyleSheet, Text, View, Image } from "react-native";
import React from "react";

const Rooms = () => {
  return (
    <View>
      <Text style={styles.textTitle}>Rooms</Text>
      <Text style={styles.textSmaller}>Room 1.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_1-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 2.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_2-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 3.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_3-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 4.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_4-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 5.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_5-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 6.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_6-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
      <Text style={styles.textSmaller}>Room 7.</Text>
      <Image
      source={require("../assets/rooms-lines-only/rum_7-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
    </View>
  );
};

export default Rooms;

const styles = StyleSheet.create({ 
  textTitle: { fontSize: 18, fontWeight: "bold", textTransform: "uppercase" },
  textSmaller: { fontSize: 12, fontWeight: "400"},
  image: {
    width: "60%", 
    minHeight: "30vh"
},
});
