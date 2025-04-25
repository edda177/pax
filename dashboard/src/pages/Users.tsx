import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from "@/components/Card";
import { User } from "../types/user";
import Button from "@/components/Button";
const Users: React.FC = () => {
  const mockUsers: User[] = [
    {
      id: 1,
      name: "Alice",
      surname: "Andersson",
      email: "alice@example.com",
      password: "password123",
      role: "admin",
    },
    {
      id: 2,
      name: "Bob",
      surname: "Berg",
      email: "bob@example.com",
      password: "securepass",
      role: "user",
    },
    {
      id: 3,
      name: "Charlie",
      surname: "Carlsson",
      email: "charlie@example.com",
      password: "charliepw",
      role: "moderator",
    },
    {
      id: 4,
      name: "Diana",
      surname: "Dahl",
      email: "diana@example.com",
      password: "dianapw",
      role: "user",
    },
  ];
  console.log(mockUsers);
  return (
    <main className="flex flex-col justify-center p-6 bg-[#10302B] gap-4 text-white w-full h-screen overflow-auto">
      <section className="flex gap-4">
        <h1 className="text-2xl font-bold text-white">Users</h1>
        <Button onClick={() => {}}>Add User</Button>
      </section>
      <section className="flex-grow gap-4 flex">
        {mockUsers.map((user) => (
          <Card key={user.id} className="h-fit">
            <CardHeader>
              <CardTitle>
                {user.name} {user.surname}
              </CardTitle>
              <CardDescription>{user.email}</CardDescription>
            </CardHeader>
            <CardContent>
              <p> Role:{user.role}</p>
            </CardContent>
            <CardFooter className="flex gap-2">
              <Button onClick={() => {}}>Update</Button>
              <Button onClick={() => {}}>Delete</Button>
            </CardFooter>
          </Card>
        ))}
      </section>
    </main>
  );
};

export default Users;
