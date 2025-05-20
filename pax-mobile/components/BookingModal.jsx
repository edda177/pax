import React, { useState, useEffect } from "react";
import {
  Modal,
  View,
  Text,
  Pressable,
  StyleSheet,
  ScrollView,
} from "react-native";
import DatePicker from "react-datepicker"; 
import "react-datepicker/dist/react-datepicker.css"; 
import { TextInput } from "react-native";

const BookingModal = ({ visible, onClose, room, onBookingSuccess, theme }) => {
  const styles = createStyles(theme);

  const [name, setName] = useState("");
  const [date, setDate] = useState(new Date());
  const [startTime, setStartTime] = useState("12:00");
  const [endTime, setEndTime] = useState("13:00");
  const [error, setError] = useState(null);
  const [success, setSuccess] = useState(false);
  const [bookings, setBookings] = useState([]);

  useEffect(() => {
    if (visible && room) {
      fetchBookings();
    }
  }, [visible, room, date]);

  const fetchBookings = async () => {
    try {
      const res = await fetch(
        "https://virtserver.swaggerhub.com/alicegmn/pax-api/dev-oas3-new/bookings"
      );
      const data = await res.json();
      const filtered = data.filter(
        (b) =>
          b.room_id === room.id && b.date === date.toISOString().split("T")[0]
      );
      setBookings(filtered);
    } catch (err) {
      console.error("Kunde inte hämta bokningar", err);
    }
  };

  const timeOverlaps = (start1, end1, start2, end2) => {
    return start1 < end2 && start2 < end1;
  };

  const handleBooking = async () => {
    if (!name || !date || !startTime || !endTime) {
      setError("Alla fält måste fyllas i.");
      return;
    }

    const [startHour, startMinute] = startTime.split(":").map(Number);
    const [endHour, endMinute] = endTime.split(":").map(Number);

    const requestedStart = startHour * 60 + startMinute;
    const requestedEnd = endHour * 60 + endMinute;

    for (let b of bookings) {
      const [bStartStr, bEndStr] = b.time.split("-");
      const [bStartH, bStartM] = bStartStr.split(":").map(Number);
      const [bEndH, bEndM] = bEndStr.split(":").map(Number);

      const bStart = bStartH * 60 + bStartM;
      const bEnd = bEndH * 60 + bEndM;

      if (timeOverlaps(requestedStart, requestedEnd, bStart, bEnd)) {
        setError("Tiden är redan bokad. Välj en annan.");
        return;
      }
    }

    try {
      const res = await fetch(
        `https://virtserver.swaggerhub.com/alicegmn/pax-api/dev-oas3-new/rooms/${room.id}/book`,
        {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({
            name,
            date: date.toISOString().split("T")[0],
            time: `${startTime}-${endTime}`,
          }),
        }
      );

      if (!res.ok) throw new Error();

      setSuccess(true);
      onBookingSuccess(room.id);

      setTimeout(() => {
        setSuccess(false);
        setName("");
        onClose();
      }, 2000);
    } catch (err) {
      setError("Det gick inte att boka rummet.");
    }
  };

  return (
    <Modal visible={visible} animationType="slide" transparent={true}>
      <View style={styles.modalBackground}>
        <View style={styles.modalContent}>
          <ScrollView>
            <Text style={styles.title}>Boka: {room?.name}</Text>

            <TextInput
              style={styles.input}
              placeholder="Ditt namn"
              value={name}
              onChangeText={setName}
              placeholderTextColor={theme.textSecondary}
            />

            <Text style={styles.label}>Välj datum:</Text>
            <DatePicker
              selected={date}
              onChange={(val) => setDate(val)}
              dateFormat="yyyy-MM-dd"
              todayButton="Idag"
              className="date-picker" // Tillämpar din stil
            />

            <Text style={styles.label}>Starttid:</Text>
            <TextInput
              style={styles.input}
              value={startTime}
              onChangeText={setStartTime}
              placeholder="Starttid (hh:mm)"
              keyboardType="numeric"
              placeholderTextColor={theme.textSecondary}
            />

            <Text style={styles.label}>Sluttid:</Text>
            <TextInput
              style={styles.input}
              value={endTime}
              onChangeText={setEndTime}
              placeholder="Sluttid (hh:mm)"
              keyboardType="numeric"
              placeholderTextColor={theme.textSecondary}
            />

            {error && <Text style={styles.error}>{error}</Text>}
            {success && <Text style={styles.success}>Bokning lyckades!</Text>}

            <Pressable style={styles.button} onPress={handleBooking}>
              <Text style={styles.buttonText}>Bekräfta bokning</Text>
            </Pressable>

            <Pressable
              style={[styles.button, { marginTop: 10 }]}
              onPress={onClose}
            >
              <Text style={styles.buttonText}>Avbryt</Text>
            </Pressable>
          </ScrollView>
        </View>
      </View>
    </Modal>
  );
};

const createStyles = (theme) =>
  StyleSheet.create({
    modalBackground: {
      flex: 1,
      backgroundColor: "rgba(0,0,0,0.5)",
      justifyContent: "center",
      alignItems: "center",
    },
    modalContent: {
      backgroundColor: theme.background,
      padding: 20,
      borderRadius: 20,
      width: "85%",
      maxHeight: "90%",
    },
    title: {
      fontSize: 18,
      fontWeight: "700",
      color: theme.textPrimary,
      marginBottom: 10,
    },
    label: {
      color: theme.textPrimary,
      marginTop: 10,
      marginBottom: 5,
    },
    input: {
      borderWidth: 1,
      borderColor: theme.textSecondary,
      borderRadius: 8,
      padding: 10,
      marginBottom: 10,
      color: theme.textPrimary,
    },
    button: {
      backgroundColor: theme.textSecondary,
      padding: 12,
      borderRadius: 8,
      alignItems: "center",
    },
    buttonText: {
      color: "#fff",
      fontWeight: "600",
    },
    error: {
      color: "red",
      textAlign: "center",
      marginBottom: 10,
    },
    success: {
      color: "green",
      textAlign: "center",
      marginBottom: 10,
    },
  });

export default BookingModal;
