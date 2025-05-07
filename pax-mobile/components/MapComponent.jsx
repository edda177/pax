import { StyleSheet, Pressable, View } from "react-native";
import React from "react"

const MapComponent = () => {
    <SafeAreaProvider>
      <SafeAreaView style={{height: 100, flexDirection: 'row'}}>
  <View name="RoomsYellow">
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
            <Image
        source={require("../assets/rooms-yellow/karta-rum_3-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-yellow/karta-rum_4-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-yellow/karta-rum_5-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-yellow/karta-rum_6-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
            <Image
        source={require("../assets/rooms-yellow/karta-rum_7-free.png")}
        style={styles.image}
        resizeMode="cover"
      />
      </View>
    <View name="RoomsRed">
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
  </SafeAreaView>
  </SafeAreaProvider>
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
