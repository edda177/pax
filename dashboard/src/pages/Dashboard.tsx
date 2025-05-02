import { useState } from "react";
import RoomCard from "@/components/RoomCard";
import { Room } from "../types/room";
import Button from "@/components/Button";
import CreateRoomModal from "@/components/CreateRoomModal";

const Dashboard: React.FC = () => {
  // Modal state
  const [isModalOpen, setIsModalOpen] = useState(false);
  // Mock room data
  const [rooms, setRooms] = useState<Room[]>([
    {
      id: 1,
      name: "Stora Konferensrummet",
      description: "Rymligt rum med plats för 20 personer.",
      available: true,
      air_quality: 95,
      screen: true,
      floor: 2,
      chairs: 20,
      whiteboard: true,
      projector: true,
    },
    {
      id: 2,
      name: "Lilla Mötesrummet",
      description: "Perfekt för mindre möten.",
      available: false,
      air_quality: 87,
      screen: false,
      floor: 1,
      chairs: 6,
      whiteboard: false,
      projector: false,
    },
    {
      id: 3,
      name: "Workshoprummet",
      description: "Flexibelt rum med bra utrustning.",
      available: true,
      air_quality: 92,
      screen: true,
      floor: 3,
      chairs: 15,
      whiteboard: true,
      projector: false,
    },
  ]);

  // Handler for add room button
  const handleAddRoom = () => {
    setIsModalOpen(true);
  };

  // Handler for modal close
  const handleCloseModal = () => {
    setIsModalOpen(false);
  };

  // Handler for room creation
  const handleCreateRoom = (roomData: Omit<Room, "id">) => {
    const newRoom: Room = {
      ...roomData,
      id: rooms.length > 0 ? Math.max(...rooms.map(r => r.id)) + 1 : 1,
    };
    setRooms(prev => [...prev, newRoom]);
    setIsModalOpen(false);
  };

  return (
    <main className="flex flex-col flex-grow bg-gray-300 min-h-screen p-6">
      <div className="flex justify-between items-center mb-6">
        <h1 className="text-2xl font-bold">Dashboard</h1>
        <Button onClick={handleAddRoom}>+ Skapa nytt rum</Button>
      </div>
      <h2 className="text-xl font-semibold mb-4">Alla rum</h2>
      {rooms.length === 0 ? (
        <p className="text-gray-500">Inga rum ännu. Skapa ett nytt rum!</p>
      ) : (
        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
          {rooms.map((room) => (
            <RoomCard
              key={room.id}
              room={room}
              onEdit={() => {}}
              onDelete={() => {}}
            />
          ))}
        </div>
      )}
      <CreateRoomModal
        isOpen={isModalOpen}
        onClose={handleCloseModal}
        onCreate={handleCreateRoom}
      />
    </main>
  );
};

export default Dashboard;
