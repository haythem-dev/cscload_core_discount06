import { pgTable, text, serial } from "drizzle-orm/pg-core";
import { createInsertSchema } from "drizzle-zod";
import { z } from "zod";

export const items = pgTable("items", {
  id: serial("id").primaryKey(),
  name: text("name").notNull(),
  description: text("description"),
});

export const insertItemSchema = createInsertSchema(items).pick({
  name: true,
  description: true,
});

export type InsertItem = z.infer<typeof insertItemSchema>;
export type Item = typeof items.$inferSelect;
