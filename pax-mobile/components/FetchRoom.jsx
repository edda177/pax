// components/FetchRoom.jsx
import React, { useEffect, useState } from "react";
import { View, Text, ActivityIndicator, StyleSheet } from "react-native";
import { useTheme } from "../theme/ThemeContext";

const FetchRoom = () => {
  const { theme } = useTheme();
  const styles = createStyles(theme);

  const [rooms, setRooms] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchRooms = async () => {
      try {
        const response = await fetch(
          "https://virtserver.swaggerhub.com/alicegmn/pax-api/dev-oas3-new/rooms"
        );
        const data = await response.json();
        const availableRooms = (data || []).filter((room) => room.available);
        setRooms(availableRooms);
      } catch (err) {
        setError("Något gick fel vid hämtning av rum.");
      } finally {
        setLoading(false);
      }
    };

    fetchRooms();
  }, []);

  if (loading) {
    return <ActivityIndicator size="large" color={theme.accent} />;
  }

  if (error) {
    return <Text style={styles.error}>{error}</Text>;
  }

  return (
    <View>
      {rooms.length === 0 ? (
        <Text style={styles.noRooms}>Inga lediga rum hittades.</Text>
      ) : (
        rooms.map((room) => (
          <View key={room.id} style={styles.roomCard}>
            <Text style={styles.roomName}>{room.name}</Text>
            <Text style={styles.roomDescription}>{room.description}</Text>
            <Text style={styles.roomDetail}>Våning: {room.floor}</Text>
            <Text style={styles.roomDetail}>Stolar: {room.chairs}</Text>
            <Text style={styles.roomDetail}>
              Luftkvalitet: {room.air_quality}
            </Text>
            <Text style={styles.roomDetail}>
              Skärm: {room.screen ? "Ja" : "Nej"} | Whiteboard:{" "}
              {room.whiteboard ? "Ja" : "Nej"} | Projektor:{" "}
              {room.projector ? "Ja" : "Nej"}
            </Text>
          </View>
        ))
      )}
    </View>
  );
};

const createStyles = (theme) =>
  StyleSheet.create({
    roomCard: {
      backgroundColor: theme.card,
      borderRadius: 16,
      padding: 12,
      marginVertical: 6,
      shadowColor: "#000",
      shadowOpacity: 0.1,
      shadowOffset: { width: 0, height: 2 },
      elevation: 2,
      width: "100%",
    },
    roomName: {
      fontSize: 18,
      fontWeight: "700",
      color: theme.textPrimary,
    },
    roomDescription: {
      fontSize: 14,
      color: theme.textSecondary,
      marginVertical: 4,
    },
    roomDetail: {
      fontSize: 13,
      color: theme.textSecondary,
    },
    noRooms: {
      fontSize: 16,
      color: theme.textSecondary,
      fontStyle: "italic",
      textAlign: "center",
    },
    error: {
      color: "red",
      fontSize: 16,
      textAlign: "center",
    },
  });

export default FetchRoom;
