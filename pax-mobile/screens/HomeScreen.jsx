import React from "react";
import { View, StyleSheet } from "react-native";
import { Calendar } from "react-native-calendars";

const HomeScreen = () => {
  const onDayPress = (day) => {
    console.log("Valt datum:", day.dateString);
  };

  return (
    <View style={styles.container}>
      <Calendar
        onDayPress={onDayPress}
        style={styles.calendar}
        theme={{
          selectedDayBackgroundColor: "#00adf5",
          todayTextColor: "#00adf5",
          arrowColor: "#00adf5",
          textMonthFontSize: 20,
        }}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 50,
    paddingHorizontal: 16,
    backgroundColor: "#f9f9f9",
  },
  calendar: {
    borderRadius: 10,
    elevation: 4,
    backgroundColor: "white",
    paddingBottom: 10,
  },
});

export default HomeScreen;
