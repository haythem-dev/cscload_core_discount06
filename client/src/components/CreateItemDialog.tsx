import { useState } from "react";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { insertItemSchema } from "@shared/schema";
import { useCreateItem } from "@/hooks/use-items";
import type { ItemInput } from "@shared/routes";
import { Dialog, DialogContent, DialogHeader, DialogTitle, DialogTrigger } from "@/components/ui/dialog";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Textarea } from "@/components/ui/textarea";
import { Form, FormControl, FormField, FormItem, FormLabel, FormMessage } from "@/components/ui/form";
import { Plus } from "lucide-react";

export function CreateItemDialog() {
  const [open, setOpen] = useState(false);
  const createItem = useCreateItem();

  const form = useForm<ItemInput>({
    resolver: zodResolver(insertItemSchema),
    defaultValues: {
      name: "",
      description: "",
    },
  });

  const onSubmit = (data: ItemInput) => {
    createItem.mutate(data, {
      onSuccess: () => {
        setOpen(false);
        form.reset();
      },
    });
  };

  return (
    <Dialog open={open} onOpenChange={setOpen}>
      <DialogTrigger asChild>
        <Button className="rounded-full shadow-lg shadow-primary/20 hover:shadow-primary/30 transition-all">
          <Plus className="w-4 h-4 mr-2" />
          Add New Item
        </Button>
      </DialogTrigger>
      <DialogContent className="sm:max-w-[425px]">
        <DialogHeader>
          <DialogTitle className="font-display text-2xl">Create Item</DialogTitle>
        </DialogHeader>
        <Form {...form}>
          <form onSubmit={form.handleSubmit(onSubmit)} className="space-y-6 pt-4">
            <FormField
              control={form.control}
              name="name"
              render={({ field }) => (
                <FormItem>
                  <FormLabel>Name</FormLabel>
                  <FormControl>
                    <Input placeholder="Enter item name..." {...field} className="rounded-lg" />
                  </FormControl>
                  <FormMessage />
                </FormItem>
              )}
            />
            <FormField
              control={form.control}
              name="description"
              render={({ field }) => (
                <FormItem>
                  <FormLabel>Description</FormLabel>
                  <FormControl>
                    <Textarea 
                      placeholder="Add a description (optional)" 
                      className="resize-none rounded-lg"
                      {...field} 
                      value={field.value || ""}
                    />
                  </FormControl>
                  <FormMessage />
                </FormItem>
              )}
            />
            <div className="flex justify-end pt-2">
              <Button type="submit" disabled={createItem.isPending} className="w-full sm:w-auto rounded-lg">
                {createItem.isPending ? "Creating..." : "Create Item"}
              </Button>
            </div>
          </form>
        </Form>
      </DialogContent>
    </Dialog>
  );
}
