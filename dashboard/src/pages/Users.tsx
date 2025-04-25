import { User } from "../types/user";
const Users: React.FC = () => {
  const mockUsers: User[] = [
    {
      id: 1,
      username: "alice",
      password: "password123",
      role: "admin",
    },
    {
      id: 2,
      username: "bob",
      password: "securepass",
      role: "user",
    },
    {
      id: 3,
      username: "charlie",
      password: "charliepw",
      role: "moderator",
    },
    {
      id: 4,
      username: "diana",
      password: "dianapw",
      role: "user",
    },
  ];
  return (
    <div>
      <h1>Users</h1>
    </div>
  );
};

export default Users;
