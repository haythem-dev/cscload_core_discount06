import { Item } from "@shared/schema";
import { Card, CardHeader, CardTitle, CardContent } from "@/components/ui/card";
import { motion } from "framer-motion";

interface ItemCardProps {
  item: Item;
  index: number;
}

export function ItemCard({ item, index }: ItemCardProps) {
  return (
    <motion.div
      initial={{ opacity: 0, y: 20 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ duration: 0.3, delay: index * 0.05 }}
    >
      <Card className="h-full border border-border/50 hover:border-primary/20 hover:shadow-md transition-all duration-300 group bg-card/50 backdrop-blur-sm">
        <CardHeader>
          <CardTitle className="font-display text-xl group-hover:text-primary transition-colors">
            {item.name}
          </CardTitle>
        </CardHeader>
        <CardContent>
          <p className="text-muted-foreground leading-relaxed">
            {item.description || "No description provided."}
          </p>
        </CardContent>
      </Card>
    </motion.div>
  );
}
