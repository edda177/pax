import React, { useState } from "react";
import { View, Text, StyleSheet, TouchableOpacity } from "react-native";
import { useTheme } from "../theme/ThemeContext";

const RoomCard = () => {
  const [bookedRoom, setBookedRoom] = useState(null);
  const { theme } = useTheme();

  const pauseBooking = () => {
    console.log("Bokningen är pausad");
  };

  const cancelBooking = () => {
    setBookedRoom(null);
    console.log("Bokningen är avbokad");
  };

  const styles = StyleSheet.create({
    card: {
      padding: 20,
      margin: 20,
      borderRadius: 12,
      backgroundColor: theme.card,
      elevation: 4,
      alignItems: "center",
    },
    title: {
      fontSize: 18,
      fontWeight: "600",
      marginBottom: 10,
      textAlign: "center",
      color: theme.textPrimary,
      fontFamily: "NunitoSans",
    },
    roomName: {
      fontSize: 16,
      fontWeight: "500",
      marginBottom: 20,
      color: theme.text,
      fontFamily: "NunitoSans",
    },
    buttonRow: {
      flexDirection: "row",
      justifyContent: "space-between",
      width: 320, // justera efter behov så det passar skärmen
      marginTop: 10,
    },
    button: {
      backgroundColor: theme.textSecondary,
      padding: 12,
      flex: 1,
      marginHorizontal: 5,
      borderRadius: 8,
      alignItems: "center",
      fontFamily: "NunitoSans",
    },
    cancelButton: {
      backgroundColor: "red",
      marginHorizontal: 5,
    },
    buttonText: {
      color: "#fff",
      fontWeight: "600",
      fontFamily: "NunitoSans",
    },
  });

  return (
    <View style={styles.card}>
      {bookedRoom ? (
        <>
          <Text style={styles.title}>Ditt rum är bokat</Text>
          <Text style={styles.roomName}>{bookedRoom.name}</Text>

          <View style={styles.buttonRow}>
            <TouchableOpacity style={styles.button} onPress={pauseBooking}>
              <Text style={styles.buttonText}>Pausa bokning</Text>
            </TouchableOpacity>

            <TouchableOpacity
              style={[styles.button, styles.cancelButton]}
              onPress={cancelBooking}
            >
              <Text style={styles.buttonText}>Avboka</Text>
            </TouchableOpacity>
          </View>
        </>
      ) : (
        <>
          <Text style={styles.title}>Du har inte bokat ett rum</Text>
          <View style={styles.buttonRow}>
            <TouchableOpacity style={styles.button} onPress={pauseBooking}>
              <Text style={styles.buttonText}>Pausa bokning</Text>
            </TouchableOpacity>

            <TouchableOpacity
              style={[styles.button, styles.cancelButton]}
              onPress={cancelBooking}
            >
              <Text style={styles.buttonText}>Avboka</Text>
            </TouchableOpacity>
          </View>
        </>
      )}
    </View>
  );
};

export default RoomCard;
