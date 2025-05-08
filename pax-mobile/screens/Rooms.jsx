import React from "react";
import { View, ScrollView, Text, Image, StyleSheet } from "react-native";
import { SafeAreaView, SafeAreaProvider } from 'react-native-safe-area-context';


const Rooms = () => {
  return (
    <SafeAreaProvider>
    <ScrollView>
  <SafeAreaView style={styles.container}>
  <Text style={styles.textTitle}>Details</Text>
  <Text style={styles.textSmaller}>Room 2</Text>
    <View style={styles.containerImage}>
      <Image
      source={require("../assets/rooms-lines-only/rum_2-no-nr.png")}
      style={styles.image}
      resizeMode="cover"/>
    </View>
    <View style={styles.textContainer}>
    <Text style={styles.textFat}>Beskrivning:</Text><Text style={styles.textSmaller}>Ett litet rum för gjord för 2-4 personer. Perfekt för enskilda samtal eller mindre möten.</Text>
    <Text style={styles.textFat}>Tillgängligt:</Text><Text style={styles.textSmaller}> Ja</Text>
    <Text style={styles.textFat}>Luftkvalité:</Text><Text style={styles.textSmaller}> 5</Text>
    <Text style={styles.textFat}>Skärm:</Text><Text style={styles.textSmaller}> false</Text>
    <Text style={styles.textFat}>Våning:</Text><Text style={styles.textSmaller}> 1</Text>
    <Text style={styles.textFat}>Platser:</Text><Text style={styles.textSmaller}> 4</Text>
    <Text style={styles.textFat}>Whiteboard:</Text><Text style={styles.textSmaller}> Ja</Text>
    <Text style={styles.textFat}>Projektor:</Text><Text style={styles.textSmaller}> Nej</Text>
    </View>
    </SafeAreaView>
    </ScrollView>
    </SafeAreaProvider>
  );
};

export default Rooms;

const styles = StyleSheet.create({ 
  container: {
    flex: 1,
    width: "100vw",
    minHeight: "70vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center"
  },
  containerImage: {
    flex: 1,
    width: "70vw",
    borderRadius: "50px",
    borderWidth: "3px",
    borderStyle: "solid",
    borderColor: "#FFFDCB",
    minHeight: "40vh",
    marginTop: "5vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#FFFDCB90"
  },
  textContainer: {
    flex: 1,
    marginTop: "5vh",
    minHeight: "60vh",
    width: "60vw",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "start",
    marginBottom: "10%",
  },
  textTitle: { 
    fontSize: 18, 
    fontWeight: "bold", 
    textAlign: "center",
    textTransform: "uppercase",
    marginBottom: "4%",
    marginTop: "2vh",
  },
  textFat: {
    marginTop: "4%",
    fontSize: 14, 
    fontWeight: "800",
    textAlign: "left"
  },
  textSmaller: { 
    fontSize: 14, 
    fontWeight: "400",
    textAlign: "left"
  },
  image: {
    width: "50vw",
    height: "30vh"
},
});
