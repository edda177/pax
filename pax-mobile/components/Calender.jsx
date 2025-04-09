import React from "react";
import { View } from "react-native";
import { Calendar } from "react-native-calendars";

const Calender = () => {
  const onDayPress = (day) => {
    console.log("Selected day", day);
  };

  return (
    <View style={{ flex: 1, padding: 10 }}>
      <Calendar
        onDayPress={onDayPress}
        markedDates={{
          "2025-04-10": { marked: true, dotColor: "red" },
          "2025-04-12": { selected: true, selectedColor: "blue" },
        }}
        theme={{
          selectedDayBackgroundColor: "#00adf5",
          todayTextColor: "#00adf5",
          arrowColor: "#00adf5",
        }}
      />
    </View>
  );
};

export default Calender;
