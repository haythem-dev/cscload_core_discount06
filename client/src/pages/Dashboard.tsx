import { useItems } from "@/hooks/use-items";
import { CreateItemDialog } from "@/components/CreateItemDialog";
import { ItemCard } from "@/components/ItemCard";
import { Loader2, PackageOpen } from "lucide-react";
import { motion } from "framer-motion";

export default function Dashboard() {
  const { data: items, isLoading, error } = useItems();

  if (isLoading) {
    return (
      <div className="min-h-screen flex items-center justify-center bg-background">
        <Loader2 className="w-8 h-8 animate-spin text-primary/50" />
      </div>
    );
  }

  if (error) {
    return (
      <div className="min-h-screen flex items-center justify-center bg-background p-4">
        <div className="text-center space-y-4">
          <p className="text-destructive font-medium">Failed to load items</p>
          <p className="text-muted-foreground text-sm">{error.message}</p>
        </div>
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-background text-foreground selection:bg-primary/10">
      <header className="border-b border-border/40 bg-background/80 backdrop-blur-md sticky top-0 z-10">
        <div className="container mx-auto px-4 h-16 flex items-center justify-between">
          <div className="flex items-center gap-2">
            <div className="w-8 h-8 bg-primary text-primary-foreground rounded-lg flex items-center justify-center font-display font-bold text-lg">
              P
            </div>
            <h1 className="font-display font-bold text-xl tracking-tight">Project Alpha</h1>
          </div>
          <CreateItemDialog />
        </div>
      </header>

      <main className="container mx-auto px-4 py-12">
        <div className="max-w-4xl mx-auto space-y-12">
          <div className="space-y-4 text-center sm:text-left">
            <motion.h2 
              initial={{ opacity: 0, y: -10 }}
              animate={{ opacity: 1, y: 0 }}
              className="text-3xl sm:text-4xl font-display font-bold tracking-tight text-primary"
            >
              Dashboard Overview
            </motion.h2>
            <motion.p 
              initial={{ opacity: 0 }}
              animate={{ opacity: 1 }}
              transition={{ delay: 0.1 }}
              className="text-lg text-muted-foreground max-w-2xl"
            >
              Manage your items and track progress in a beautifully minimal interface designed for clarity and focus.
            </motion.p>
          </div>

          {!items || items.length === 0 ? (
            <motion.div 
              initial={{ opacity: 0, scale: 0.95 }}
              animate={{ opacity: 1, scale: 1 }}
              className="flex flex-col items-center justify-center py-20 border-2 border-dashed border-border/60 rounded-2xl bg-muted/20"
            >
              <div className="w-16 h-16 rounded-full bg-muted flex items-center justify-center mb-4">
                <PackageOpen className="w-8 h-8 text-muted-foreground" />
              </div>
              <h3 className="text-xl font-semibold mb-2">No items yet</h3>
              <p className="text-muted-foreground mb-6 max-w-sm text-center">
                Get started by creating your first item. It will appear here immediately.
              </p>
              <CreateItemDialog />
            </motion.div>
          ) : (
            <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
              {items.map((item, i) => (
                <ItemCard key={item.id} item={item} index={i} />
              ))}
            </div>
          )}
        </div>
      </main>
    </div>
  );
}
