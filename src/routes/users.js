import express from "express";
import pool from "../db.js";

const router = express.Router();

// Create a new user
router.post("/", async (req, res) => {
  const { name, email, password, role } = req.body;

  try {
    const result = await pool.query(
      `INSERT INTO users (name, email, password, role)
       VALUES ($1, $2, $3, $4)
       RETURNING id, name, email, role`,
      [name, email, password, role || "user"]
    );
    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error("Error creating user:", err);
    res.status(500).json({ error: "Error creating user" });
  }
});

// GET all users
router.get("/", async (req, res) => {
  try {
    const result = await pool.query("SELECT * FROM users");
    res.json(result.rows);
  } catch (err) {
    console.error("Error fetching users:", err);
    res.status(500).json({ error: "Error fetching users" });
  }
});

// GET a specific user
router.get("/:id", async (req, res) => {
  const { id } = req.params;

  try {
    const result = await pool.query(
      "SELECT id, name, email, role FROM users WHERE id = $1",
      [id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "User not found" });
    }

    res.json(result.rows[0]);
  } catch (err) {
    console.error("Error fetching user:", err);
    res.status(500).json({ error: "Error fetching user" });
  }
});

// Update a user
router.put("/:id", async (req, res) => {
  const { id } = req.params;
  const { name, email, role } = req.body;

  try {
    const result = await pool.query(
      `UPDATE users SET name = $1, email = $2, role = $3
       WHERE id = $4 RETURNING id, name, email, role`,
      [name, email, role, id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "User not found" });
    }

    res.json(result.rows[0]);
  } catch (err) {
    console.error("Error updating user:", err);
    res.status(500).json({ error: "Error updating user" });
  }
});

// Delete a user
router.delete("/:id", async (req, res) => {
  const { id } = req.params;

  try {
    const result = await pool.query(
      "DELETE FROM users WHERE id = $1 RETURNING *",
      [id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "User not found" });
    }

    res.json({ message: "User deleted", user: result.rows[0] });
  } catch (err) {
    console.error("Error deleting user:", err);
    res.status(500).json({ error: "Error deleting user" });
  }
});

export default router;

// To do
// Inloggning (POST /login) med bcrypt och jsonwebtoken
// Middleware för att skydda admin-only routes
// Validering med t.ex. zod eller express-validator
